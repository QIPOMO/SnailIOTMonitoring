#include "databasemessage.h"

// 初始化静态成员
DatabaseMessage* DatabaseMessage::m_instance = nullptr;
QMutex DatabaseMessage::m_instanceMutex;

DatabaseMessage* DatabaseMessage::instance()
{
    QMutexLocker locker(&m_instanceMutex);
    if (!m_instance) {
        m_instance = new DatabaseMessage();
    }
    return m_instance;
}

DatabaseMessage::DatabaseMessage(QObject *parent) : QObject(parent)
{
    // 初始化时不打开数据库，需要显式调用openDatabase
}

DatabaseMessage::~DatabaseMessage()
{
    closeDatabase();
}

bool DatabaseMessage::openDatabase(const QString &databaseName)
{
    QMutexLocker locker(&m_dbMutex);

    if (m_db.isOpen()) {
        return true;
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE", "user_connection");
    m_db.setDatabaseName(databaseName);

    if (!m_db.open()) {
        qDebug() << "Error: Could not open user database:" << m_db.lastError().text();
        return false;
    }

    return createTables();
}

void DatabaseMessage::closeDatabase()
{
    QMutexLocker locker(&m_dbMutex);
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseMessage::isOpen() const
{
    QMutexLocker locker(&m_dbMutex);
    return m_db.isOpen();
}

QString DatabaseMessage::hashPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
    );
    return QString(hash.toHex());
}

bool DatabaseMessage::createTables()
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QString createUsersTable =
        "CREATE TABLE IF NOT EXISTS users ("
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL COLLATE NOCASE, "
        "password TEXT NOT NULL, "
        "email TEXT UNIQUE NOT NULL COLLATE NOCASE, "
        "phone TEXT UNIQUE NOT NULL, "
        "nickname TEXT, "
        "role TEXT NOT NULL DEFAULT 'user', "
        "created_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
        "last_modified TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
        "CONSTRAINT chk_role CHECK (role IN ('admin', 'user')))";

    if (!query.prepare(createUsersTable) || !query.exec()) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }

    // 创建索引
    QStringList indexQueries = {
        "CREATE INDEX IF NOT EXISTS idx_users_username ON users(username)",
        "CREATE INDEX IF NOT EXISTS idx_users_email ON users(email)",
        "CREATE INDEX IF NOT EXISTS idx_users_phone ON users(phone)"
    };

    for (const QString &sql : indexQueries) {
        if (!query.exec(sql)) {
            qDebug() << "Error creating index:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

bool DatabaseMessage::executeQuery(QSqlQuery &query)
{
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        qDebug() << "Executed SQL:" << query.lastQuery();
        return false;
    }
    return true;
}

bool DatabaseMessage::prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params)
{
    if (!query.prepare(sql)) {
        qDebug() << "Prepare error:" << query.lastError().text();
        return false;
    }

    // 绑定所有参数
    for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
        query.bindValue(it.key(), it.value());
    }

    return executeQuery(query);
}

bool DatabaseMessage::addUser(const QString &name, const QString &password,
                             const QString &email, const QString &phone,
                             const QString &nickname, const QString &role)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    // 检查必填字段
    if (name.isEmpty() || password.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        qDebug() << "Error: Required fields are missing";
        return false;
    }

    // 检查用户名是否已存在
    if (getUserByName(name).user_id != 0) {
        qDebug() << "Error: Username already exists";
        return false;
    }

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);
    params.insert(":password", hashPassword(password));
    params.insert(":email", email);
    params.insert(":phone", phone);
    params.insert(":nickname", nickname);
    params.insert(":role", role);

    return prepareQuery(query,
                      "INSERT INTO users (username, password, email, phone, nickname, role) "
                      "VALUES (:name, :password, :email, :phone, :nickname, :role)",
                      params);
}

bool DatabaseMessage::deleteUser(int user_id)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user_id);

    return prepareQuery(query,
                       "DELETE FROM users WHERE user_id = :user_id",
                       params);
}

bool DatabaseMessage::deleteUserByName(const QString &name)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    return prepareQuery(query,
                       "DELETE FROM users WHERE username = :name",
                       params);
}

bool DatabaseMessage::updateUserEmail(const QString &name, const QString &newEmail)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    // 检查邮箱格式
    if (!newEmail.contains('@') || !newEmail.contains('.')) {
        qDebug() << "Error: Invalid email format";
        return false;
    }

    // 获取当前用户
    Users user = getUserByName(name);
    if (user.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    // 检查邮箱是否已被使用
    Users emailUser = getUserByEmail(newEmail);
    if (emailUser.user_id != 0 && emailUser.user_id != user.user_id) {
        qDebug() << "Error: Email already in use";
        return false;
    }

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user.user_id);
    params.insert(":email", newEmail);

    return prepareQuery(query,
                       "UPDATE users SET email = :email WHERE user_id = :user_id",
                       params);
}

bool DatabaseMessage::updateUserphone(const QString &name, const QString &newphone)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    // 获取当前用户
    Users user = getUserByName(name);
    if (user.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    // 检查手机号是否已被使用
    Users phoneUser = getUserByPhone(newphone);
    if (phoneUser.user_id != 0 && phoneUser.user_id != user.user_id) {
        qDebug() << "Error: Phone number already in use";
        return false;
    }

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user.user_id);
    params.insert(":phone", newphone);

    return prepareQuery(query,
                       "UPDATE users SET phone = :phone WHERE user_id = :user_id",
                       params);
}

bool DatabaseMessage::updateUserrole(const QString &name, const QString &newrole)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    // 验证角色值
    if (newrole != "user" && newrole != "admin") {
        qDebug() << "Error: Invalid role value";
        return false;
    }

    // 获取当前用户
    Users user = getUserByName(name);
    if (user.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user.user_id);
    params.insert(":role", newrole);

    return prepareQuery(query,
                       "UPDATE users SET role = :role WHERE user_id = :user_id",
                       params);
}

bool DatabaseMessage::updatePasswordByEmailOrPhone(const QString &emailOrPhone, const QString &newPassword)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    if (newPassword.isEmpty()) {
        qDebug() << "Error: New password cannot be empty";
        return false;
    }

    // 判断是邮箱还是手机号
    Users user;
    if (emailOrPhone.contains('@')) {
        user = getUserByEmail(emailOrPhone);
    } else {
        user = getUserByPhone(emailOrPhone);
    }

    if (user.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    return updateUserPassword(user.user_id, newPassword);
}

bool DatabaseMessage::updateUserPassword(int user_id, const QString &newPassword)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    if (newPassword.isEmpty()) {
        qDebug() << "Error: New password cannot be empty";
        return false;
    }

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user_id);
    params.insert(":password", hashPassword(newPassword));

    return prepareQuery(query,
                       "UPDATE users SET password = :password WHERE user_id = :user_id",
                       params);
}

bool DatabaseMessage::authenticateUser(const QString &name, const QString &password)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    Users user = getUserByName(name);
    if (user.user_id == 0) {
        return false; // 用户不存在
    }

    return user.password == hashPassword(password);
}

QVector<DatabaseMessage::Users> DatabaseMessage::getAllUsers()
{
    QMutexLocker locker(&m_dbMutex);
    QVector<Users> users;
    if (!isOpen()) return users;

    QSqlQuery query("SELECT user_id, username, password, email, phone, nickname, role FROM users", m_db);
    while (query.next()) {
        Users user;
        user.user_id = query.value("user_id").toInt();
        user.username = query.value("username").toString();
        user.password = query.value("password").toString();
        user.email = query.value("email").toString();
        user.phone = query.value("phone").toString();
        user.nickname = query.value("nickname").toString();
        user.role = query.value("role").toString();
        users.append(user);
    }

    return users;
}

DatabaseMessage::Users DatabaseMessage::getUserById(int user_id)
{
    QMutexLocker locker(&m_dbMutex);
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user_id);

    if (prepareQuery(query,
                    "SELECT user_id, username, password, email, phone, nickname, role "
                    "FROM users WHERE user_id = :user_id",
                    params)) {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("username").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }

    return user;
}

DatabaseMessage::Users DatabaseMessage::getUserByName(const QString &name)
{
    QMutexLocker locker(&m_dbMutex);
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    if (prepareQuery(query,
                     "SELECT user_id, username, password, email, phone, nickname, role "
                     "FROM users WHERE username = :name",
                    params)) {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("username").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }
    return user;
}

DatabaseMessage::Users DatabaseMessage::getUserByEmail(const QString &Email)
{
    QMutexLocker locker(&m_dbMutex);
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":email", Email);

    if (prepareQuery(query,
                   "SELECT user_id, username, password, email, phone, nickname, role "
                   "FROM users WHERE email = :email",
                   params)) {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("username").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }
    return user;
}

DatabaseMessage::Users DatabaseMessage::getUserByPhone(const QString &Phone)
{
    QMutexLocker locker(&m_dbMutex);
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":phone", Phone);

    if (prepareQuery(query,
                   "SELECT user_id, username, password, email, phone, nickname, role "
                   "FROM users WHERE phone = :phone",
                   params)) {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("username").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }
    return user;
}

bool DatabaseMessage::userExists(const QString &name)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    if (!prepareQuery(query,
                     "SELECT COUNT(*) FROM users WHERE username = :name",
                     params)) {
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
