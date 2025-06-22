#include "databasemessage.h"

/**
 * @brief 构造函数，初始化数据库连接
 * @param parent 父对象指针，用于Qt对象树管理
 *
 * 创建SQLite数据库连接，使用"user_connection"作为唯一连接名，
 * 避免多线程环境下的连接冲突
 */
DatabaseMessage::DatabaseMessage(QObject *parent)
    : QObject(parent) {
    //m_db = QSqlDatabase::addDatabase("QSQLITE", "user_connection"); // 使用自定义连接名
}

/**
 * @brief 析构函数，自动关闭数据库连接
 */
DatabaseMessage::~DatabaseMessage() {
    closeDatabase();
}

/**
 * @brief 创建数据库表（内部初始化用）
 * @return 创建成功返回true，失败返回false
 */
bool DatabaseMessage::createTables()
{
    QSqlQuery query(m_db);
    // 创建设备表的SQL语句
    QString createUsersTable =
            "CREATE TABLE IF NOT EXISTS users ("
            "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "     // 自增主键
            "name TEXT UNIQUE NOT NULL, "                // 用户名，唯一，非空
            "password TEXT NOT NULL, "                       // 密码，非空，加密存储
            "email TEXT UNIQUE NOT NULL, "                   // 邮箱，唯一，非空
            "phone TEXT UNIQUE NOT NULL, "                   // 手机号，唯一，非空
            "nickname TEXT, "                                // 昵称，可空
            "role TEXT NOT NULL DEFAULT 'user', "            // 角色，默认普通用户
            "CONSTRAINT chk_role CHECK (role IN ('admin', 'user')))";  // 角色检查约束

    // 执行创建表语句
    if (!query.exec(createUsersTable)) {
        qDebug() << "Error creating devices table:" << query.lastError().text();
        return false;
    }
    return true;
}

/**
 * @brief 打开指定名称的SQLite数据库
 * @param databaseName 数据库文件名（默认为"users.db"）
 * @return 成功打开返回true，失败返回false
 *
 * 如果数据库文件不存在会自动创建，并确保必要的表结构已初始化
 */
bool DatabaseMessage::openDatabase(const QString &databaseName)
{
    if (m_db.isOpen()) return true;

    // 只在需要时创建连接
    if (QSqlDatabase::contains("user_connection")) {
        m_db = QSqlDatabase::database("user_connection");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "user_connection");
    }

    m_db.setDatabaseName(databaseName);
    // 尝试打开数据库
    if (!m_db.open()) {
        qDebug() << "Error: Could not open device database:" << m_db.lastError().text();
        return false;
    }

    // 创建必要的表结构
    return createTables();
}

/**
 * @brief 关闭数据库连接
 *
 * 安全关闭当前数据库连接，如果连接已关闭则不做任何操作
 */
void DatabaseMessage::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

/**
 * @brief 检查数据库连接状态
 * @return 数据库已连接返回true，否则返回false
 */
bool DatabaseMessage::isOpen() const
{
    return m_db.isOpen();
}


/**
 * @brief 添加新用户到数据库
 * @param name 用户名
 * @param password 原始密码（会自动加密存储）
 * @return 添加成功返回true，失败返回false
 *
 * 会先检查用户名是否已存在，密码会自动进行SHA-256加密后存储
 */
bool DatabaseMessage::addUser(const QString &name, const QString &password,const QString &email,const QString &phone,const QString &nickname,const QString &role)
{
    if (!isOpen()) return false;

    //检查用户名是否已存在
//    if (getUserByName(name).user_id != 0) {
//        qDebug() << "Error: Username already exists";
//        return false;
//    }
    // 检查必填字段
    if (name.isEmpty() || password.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        qDebug() << "Error: Username is required";
        return false;
    }

    if (password.isEmpty()) {
        qDebug() << "Error: password is required";
        return false;
    }

    if ( email.isEmpty() ) {
        qDebug() << "Error: email is required";
        return false;
    }

    if (phone.isEmpty()) {
        qDebug() << "Error: phone is required";
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
                        "INSERT INTO users (name, password, email, phone, nickname, role) "
                        "VALUES (:name, :password, :email, :phone, :nickname, :role)",
                        params);
}

/**
 * @brief 根据用户ID删除用户
 * @param id 要删除的用户ID
 * @return 删除成功返回true，失败返回false
 */
bool DatabaseMessage::deleteUser(int user_id)
{
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user_id);

    return prepareQuery(query,
                        "DELETE FROM users WHERE user_id = :user_id",
                        params);
}

/**
 * @brief 根据用户名删除用户
 * @param name 要删除的用户名
 * @return 删除成功返回true，失败返回false
 */
bool DatabaseMessage::deleteUserByName(const QString &name)
{
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    return prepareQuery(query,
                        "DELETE FROM users WHERE name = :name",
                        params);
}

/**
 * @brief 更新邮箱
 * @param name要更新的用户的名字
 * @param newEmail新的邮箱
 * @return 更新成功返回true，失败返回false
 *
 * 会检查新邮箱是否已被其他用户使用
 */
bool DatabaseMessage::updateUserEmail(const QString &name, const QString &newEmail)
{
    // 检查数据库连接
    if (!isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    // 检查邮箱格式是否有效（简单验证）
    if (!newEmail.contains('@') || !newEmail.contains('.')) {
        qDebug() << "Error: Invalid email format";
        return false;
    }

    // 获取当前用户信息
    Users existingUser = getUserByName(name);
    if (existingUser.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    // 检查新邮箱是否已被其他用户使用
    Users emailUser = getUserByEmail(newEmail);
    if (emailUser.user_id != 0 && emailUser.user_id != existingUser.user_id) {
        qDebug() << "Error: Email already in use by another user";
        return false;
    }

    // 准备更新查询
    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", existingUser.user_id);  // 使用user_id作为条件更可靠
    params.insert(":email", newEmail);

    return prepareQuery(query,
                        "UPDATE users SET email = :email WHERE user_id = :user_id",
                        params);
}

bool DatabaseMessage::updateUserphone(const QString &name, const QString &newphone) {
    // 检查数据库连接
    if (!isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    // 获取当前用户信息
    Users existingUser = getUserByName(name);
    if (existingUser.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    // 准备更新查询
    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", existingUser.user_id);  // 使用user_id作为条件更可靠
    params.insert(":phone", newphone);

    return prepareQuery(query,
                        "UPDATE users SET phone = :phone WHERE user_id = :user_id",
                        params);
}

bool DatabaseMessage::updateUserrole(const QString &name, const QString &newrole) {
    // 检查数据库连接
    if (!isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    // 获取当前用户信息
    Users existingUser = getUserByName(name);
    if (existingUser.user_id == 0) {
        qDebug() << "Error: User not found";
        return false;
    }

    // 准备更新查询
    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", existingUser.user_id);  // 使用user_id作为条件更可靠
    params.insert(":role", newrole);

    return prepareQuery(query,
                        "UPDATE users SET role = :role WHERE user_id = :user_id",
                        params);
}


bool DatabaseMessage::updatePasswordByEmailOrPhone(const QString &emailOrPhone, const QString &newPassword) {
    if (!isOpen()) {
        qDebug() << "Error: Database not connected";
        return false;
    }

    // 检查新密码是否为空
    if (newPassword.isEmpty()) {
        qDebug() << "Error: New password cannot be empty";
        return false;
    }

    // 根据邮箱或手机号查找用户
    Users user;
    QSqlQuery query(m_db);

    // 判断输入是邮箱还是手机号（简单逻辑，实际项目需更严格的验证）
    bool isEmail = emailOrPhone.contains('@');

    if (isEmail) {
        user = getUserByEmail(emailOrPhone);
    } else {
        // 假设输入是手机号（实际项目应验证手机号格式）
        QVariantMap params;
        params.insert(":phone", emailOrPhone);
        if (prepareQuery(query,
                         "SELECT user_id, name FROM users WHERE phone = :phone",
                         params)) {
            if (query.next()) {
                user.user_id = query.value("user_id").toInt();
                user.username = query.value("name").toString();
            }
        }
    }

    // 检查用户是否存在
    if (user.user_id == 0) {
        qDebug() << "Error: User not found with provided email/phone";
        return false;
    }

    // 更新密码
    QVariantMap updateParams;
    updateParams.insert(":user_id", user.user_id);
    updateParams.insert(":password", hashPassword(newPassword));

    return prepareQuery(query,
                        "UPDATE users SET password = :password WHERE user_id = :user_id",
                        updateParams);
}
/**
 * @brief 更新用户密码
 * @param id 要更新的用户ID
 * @param newPassword 新的原始密码（会自动加密存储）
 * @return 更新成功返回true，失败返回false
 */
bool DatabaseMessage::updateUserPassword(int user_id, const QString &newPassword)
{
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user_id);
    params.insert(":password", hashPassword(newPassword));

    return prepareQuery(query,
                        "UPDATE users SET password = :password WHERE user_id = :user_id",
                        params);
}

/**
 * @brief 用户认证
 * @param name 用户名
 * @param password 待验证的原始密码
 * @return 认证成功返回true，失败返回false
 *
 * 会比较加密后的密码是否匹配
 */
bool DatabaseMessage::authenticateUser(const QString &name, const QString &password)
{
    Users user = getUserByName(name);
    if (user.user_id == 0) {
        return false; // 用户不存在
    }

    return user.password == hashPassword(password);
}

/**
 * @brief 获取所有用户列表
 * @return 包含所有用户的QVector
 */
QVector<DatabaseMessage::Users> DatabaseMessage::getAllUsers()
{
    QVector<Users> users;
    if (!isOpen()) return users;

    QSqlQuery query("SELECT user_id, name, password,email,phone,nickname,role FROM users", m_db);
    while (query.next()) {
        Users user;
        user.user_id = query.value("user_id").toInt();
        user.username = query.value("name").toString();
        user.password = query.value("password").toString();
        user.email = query.value("email").toString();
        user.phone = query.value("phone").toString();
        user.nickname = query.value("nickname").toString();
        user.role = query.value("role").toString();
        users.append(user);
    }

    return users;
}

/**
 * @brief 根据ID获取单个用户信息
 * @param id 用户ID
 * @return 包含用户信息的User结构体，如果不存在则返回空结构体
 */
DatabaseMessage::Users DatabaseMessage::getUserById(int user_id)
{
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":user_id", user_id);

    if (prepareQuery(query,
                     "SELECT user_id, name, password FROM users WHERE user_id = :user_id",
                     params)) {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("name").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }

    return user;
}

/**
 * @brief 根据用户名获取单个用户信息
 * @param name 用户名
 * @return 包含用户信息的User结构体，如果不存在则返回空结构体
 */
DatabaseMessage::Users DatabaseMessage::getUserByName(const QString &name)
{
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    if (prepareQuery(query,
                     "SELECT user_id, name, password, email, phone, nickname, role "
                     "FROM users WHERE name = :name",
                     params)) {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("name").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }
    return user;
}

DatabaseMessage::Users DatabaseMessage::getUserByEmail(const QString &Email) {
    Users user;
    if (!isOpen()) return user;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":email", Email); // 使用email作为查询参数

    if (prepareQuery(query,
                     "SELECT user_id, name, password, email, phone, nickname, role "
                     "FROM users WHERE email = :email",
                     params))
    {
        if (query.next()) {
            user.user_id = query.value("user_id").toInt();
            user.username = query.value("name").toString();
            user.password = query.value("password").toString();
            user.email = query.value("email").toString();
            user.phone = query.value("phone").toString();
            user.nickname = query.value("nickname").toString();
            user.role = query.value("role").toString();
        }
    }
    else {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    return user;
}

bool DatabaseMessage::userExists(const QString &name) {
    // 检查数据库连接
    if (!isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    // 准备查询
    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    // 执行查询
    if (!prepareQuery(query,
                      "SELECT COUNT(*) FROM users WHERE name = :name",
                      params)) {
        qDebug() << "Error: Failed to prepare query";
        return false;
    }

    // 获取结果
    if (query.next()) {
        return query.value(0).toInt() > 0;  // 如果计数>0则用户存在
    }
    return false;
}

QString DatabaseMessage::hashPassword(const QString &password) {
    // 使用SHA-256加密密码
    QByteArray hash = QCryptographicHash::hash(
                password.toUtf8(),
                QCryptographicHash::Sha256
                );
    return QString(hash.toHex());
}

/**
 * @brief 执行SQL查询（内部方法）
 * @param query 已准备好的QSqlQuery对象
 * @return 执行成功返回true，失败返回false
 *
 * 如果执行失败会自动打印错误信息和执行的SQL语句
 */
bool DatabaseMessage::executeQuery(QSqlQuery &query)
{
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        qDebug() << "Executed SQL:" << query.lastQuery();
        return false;
    }
    return true;
}

/**
 * @brief 准备并执行参数化查询（内部方法）
 * @param query QSqlQuery对象
 * @param sql SQL语句字符串
 * @param params 参数键值对（可选）
 * @return 准备和执行成功返回true，失败返回false
 *
 * 使用参数化查询防止SQL注入，自动绑定参数值
 */
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
