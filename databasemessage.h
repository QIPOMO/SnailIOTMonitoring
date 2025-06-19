#ifndef DATABASEMESSAGE_H
#define DATABASEMESSAGE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QThreadStorage>
#include <QSqlRecord>
#include <QThread>
#include <QCryptographicHash>

class DatabaseMessage : public QObject
{
    Q_OBJECT
public:
    struct Users {
        int user_id;
        QString username;
        QString password;
        QString email;
        QString phone;
        QString nickname;
        QString role;
    };

    // 获取单例实例
    static DatabaseMessage* instance();

    // 禁止拷贝和赋值
    DatabaseMessage(const DatabaseMessage&) = delete;
    DatabaseMessage& operator=(const DatabaseMessage&) = delete;

    bool openDatabase(const QString &databaseName = "users.db");
    void closeDatabase();
    bool isOpen() const;

    bool addUser(const QString &name, const QString &password, const QString &email,
                const QString &phone, const QString &nickname = "", const QString &role = "user");
    bool deleteUser(int user_id);
    bool deleteUserByName(const QString &name);
    bool updateUserEmail(const QString &name, const QString &newEmail);
    bool updateUserphone(const QString &name, const QString &newphone);
    bool updateUserrole(const QString &name, const QString &newrole);
    bool updatePasswordByEmailOrPhone(const QString &emailOrPhone, const QString &newPassword);
    bool updateUserPassword(int user_id, const QString &newPassword);
    bool authenticateUser(const QString &name, const QString &password);
    QVector<Users> getAllUsers();
    Users getUserById(int user_id);
    Users getUserByName(const QString &name);
    Users getUserByEmail(const QString &Email);
    Users getUserByPhone(const QString &Phone);
    bool userExists(const QString &name);

private:
    // 私有构造函数
    explicit DatabaseMessage(QObject *parent = nullptr);
    ~DatabaseMessage();

    static DatabaseMessage* m_instance;
    static QMutex m_instanceMutex;

    QSqlDatabase m_db;
    mutable QMutex m_dbMutex;

    QString hashPassword(const QString &password);
    bool createTables();
    bool executeQuery(QSqlQuery &query);
    bool prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params = QVariantMap());
};

#endif // DATABASEMESSAGE_H
