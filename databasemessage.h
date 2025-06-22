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
#include <QCryptographicHash> // 用于密码加密

/**
 * @brief 线程安全的SQLite数据库管理类
 *
 * 封装了常见的数据库操作，支持多线程环境下的安全访问
 * 提供用户数据的增删改查及认证功能，密码自动加密存储
 */
class DatabaseMessage : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，用于Qt对象树管理
     */
    DatabaseMessage(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     * 自动关闭数据库连接
     */
    ~DatabaseMessage();

    // 数据库连接管理

    /**
     * @brief 打开数据库连接
     * @param databaseName 数据库文件名，默认为"users.db"
     * @return 成功打开返回true，失败返回false
     */
    bool openDatabase(const QString &databaseName = "users.db");

    /**
     * @brief 关闭数据库连接
     */
    void closeDatabase();

    /**
     * @brief 检查数据库是否已打开
     * @return 数据库已打开返回true，否则返回false
     */
    bool isOpen() const;

    // 用户数据结构
    /**
     * @brief 用户数据结构体
     * 表示数据库中的用户记录
     */
    struct Users {
        int user_id;            ///< 用户ID，主键
        QString username;       ///< 用户名
        QString password;       ///< 加密后的密码
        QString email;          ///< 用户邮件
        QString phone;          ///< 用户手机号
        QString nickname;       ///< 用户昵称
        QString role;           ///< 用户角色
    };


    // 用户操作

    /**
     * @brief 添加新用户
     * @param name 用户名
     * @param password 原始密码（会自动加密存储）
     * @return 操作成功返回true，失败返回false
     */
    bool addUser(const QString &name, const QString &password,const QString &email,const QString &phone,const QString &nickname=nullptr,const QString &role="user");

    /**
     * @brief 根据ID删除用户
     * @param id 要删除的用户ID
     * @return 操作成功返回true，失败返回false
     */
    bool deleteUser(int user_id);

    /**
     * @brief 根据用户名删除用户
     * @param name 要删除的用户名
     * @return 操作成功返回true，失败返回false
     */
    bool deleteUserByName(const QString &name);

    /**
     * @brief 更新邮件
     * @param name要更新的用户
     * @param newEmail 新的用户邮件
     * @return 操作成功返回true，失败返回false
     */
    bool updateUserEmail(const QString &name, const QString &newEmail);

    /**
     * @brief 更新手机号
     * @param name要更新的用户
     * @param newphone 新的用户是手机号
     * @return 操作成功返回true，失败返回false
     */
    bool updateUserphone(const QString &name, const QString &newphone);

    /**
     * @brief 更新角色
     * @param name要更新的用户
     * @param newrole 修改的用户的角色
     * @return 操作成功返回true，失败返回false
     */
    bool updateUserrole(const QString &name, const QString &newrole);

    /**
     * @brief 更新用户密码
     * @param id 要更新的用户ID
     * @param newPassword 新的原始密码（会自动加密存储）
     * @return 操作成功返回true，失败返回false
     */
    bool updateUserPassword(int user_id, const QString &newPassword);

    bool updatePasswordByEmailOrPhone(const QString &emailOrPhone, const QString &newPassword);


    /**
     * @brief 用户认证
     * @param name 用户名
     * @param password 待验证的原始密码
     * @return 认证成功返回true，失败返回false
     */
    bool authenticateUser(const QString &name, const QString &password);

    /**
     * @brief 获取所有用户列表
     * @return 包含所有用户的QVector
     */
    QVector<Users> getAllUsers();

    /**
     * @brief 根据ID获取用户信息
     * @param id 用户ID
     * @return 包含用户信息的User结构体，如果不存在则返回空结构体
     */
    Users getUserById(int user_id);

    /**
     * @brief 根据用户名获取用户信息
     * @param name 用户名
     * @return 包含用户信息的User结构体，如果不存在则返回空结构体
     */
    Users getUserByName(const QString &name);

    Users getUserByEmail(const QString &Email);
    /**
     * @brief 检查用户是否存在
     * @param name 用户名
     * @return 用户存在返回true，否则返回false
     */
    bool userExists(const QString &name);


private:
    QSqlDatabase m_db;  ///< SQLite数据库连接对象

    /**
     * @brief 密码哈希函数
     * @param password 原始密码
     * @return 加密后的密码字符串
     */
    QString hashPassword(const QString &password);

    /**
     * @brief 执行SQL查询
     * @param query 已准备好的QSqlQuery对象
     * @return 执行成功返回true，失败返回false
     */
    bool executeQuery(QSqlQuery &query);

    /**
     * @brief 准备SQL查询
     * @param query QSqlQuery对象
     * @param sql SQL语句字符串
     * @param params 参数键值对（可选）
     * @return 准备成功返回true，失败返回false
     */
    bool prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params = QVariantMap());

    /**
     * @brief 创建数据库表（内部初始化用）
     * @return 创建成功返回true，失败返回false
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H
