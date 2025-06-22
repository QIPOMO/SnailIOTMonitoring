#ifndef DATABASEDEVICE_H
#define DATABASEDEVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QDateTime>

/**
 * @brief 设备数据库管理类（单线程版）
 *
 * 提供设备信息的CRUD操作，使用SQLite作为后端存储。
 * 注意：此类设计为单线程使用，多线程环境需额外加锁。
 */
class DatabaseDevice : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 设备数据结构体
     */
    struct Device {
        int device_id;          ///< 设备唯一ID（主键）
        QString name;           ///< 设备名称（唯一）
        QString type;           ///< 设备类型（如CNC/Sensor）
        QString status;         ///< 运行状态（运行中/待机/故障）
        QString location;       ///< 物理位置
        QString description;    ///< 详细描述（可选）
        QDateTime last_maintenance; ///< 最后维护时间
        QDateTime created_at;   ///< 设备录入时间
    };

    /**
     * @brief 构造函数
     * @param parent Qt父对象指针，用于内存管理
     */
    explicit DatabaseDevice(QObject *parent = nullptr);

    /**
     * @brief 析构函数
     * 自动关闭数据库连接
     */
    ~DatabaseDevice();

    // 数据库连接管理
    /**
     * @brief 打开数据库连接
     * @param databaseName 数据库文件路径（默认"users.db"）
     * @return 成功打开返回true，失败返回false
     * @note 如果数据库文件不存在会自动创建
     */
    bool openDatabase(const QString &databaseName = "users.db");

    /**
     * @brief 关闭数据库连接
     */
    void closeDatabase();

    /**
     * @brief 检查数据库连接状态
     * @return 已连接返回true，否则false
     */
    bool isOpen() const;

    // 设备CRUD操作
    /**
     * @brief 添加新设备
     * @param name 设备名称（必填）
     * @param type 设备类型（必填）
     * @param status 初始状态（必填）
     * @param location 安装位置（必填）
     * @param description 描述信息（可选）
     * @param last_maintenance 最后维护时间（可选，默认当前时间）
     * @return 操作成功返回true
     * @warning 设备名称必须唯一
     */
    bool addDevice(const QString &name, const QString &type,
                  const QString &status, const QString &location,
                  const QString &description = "",
                  const QDateTime &last_maintenance = QDateTime());

    /**
     * @brief 删除设备（通过ID）
     * @param device_id 要删除的设备ID
     * @return 操作成功返回true
     */
    bool deleteDevice(int device_id);

    /**
     * @brief 删除设备（通过名称）
     * @param name 要删除的设备名称
     * @return 操作成功返回true
     */
    bool deleteDeviceByName(const QString &name);

    // 设备信息更新
    bool updateDeviceName(int device_id, const QString &newName);
    bool updateDeviceType(int device_id, const QString &newType);
    bool updateDeviceStatus(int device_id, const QString &newStatus);
    bool updateDeviceLocation(int device_id, const QString &newLocation);
    bool updateDeviceDescription(int device_id, const QString &newDesc);
    bool updateLastMaintenance(int device_id, const QDateTime &newTime);

    // 设备查询
    /**
     * @brief 获取所有设备列表
     * @return 按device_id排序的设备向量
     */
    QVector<Device> getAllDevices();

    /**
     * @brief 通过ID获取单个设备
     * @param device_id 设备ID
     * @return 设备信息，如果不存在返回空结构体
     */
    Device getDeviceById(int device_id);

    /**
     * @brief 通过名称获取单个设备
     * @param name 设备名称
     * @return 设备信息，如果不存在返回空结构体
     */
    Device getDeviceByName(const QString &name);

    /**
     * @brief 按类型筛选设备
     * @param type 设备类型（如"CNC"）
     * @return 匹配该类型的所有设备
     */
    QVector<Device> getDevicesByType(const QString &type);

    /**
     * @brief 按状态筛选设备
     * @param status 状态（如"运行中"）
     * @return 匹配该状态的所有设备
     */
    QVector<Device> getDevicesByStatus(const QString &status);

    /**
     * @brief 按位置筛选设备
     * @param location 物理位置（如"车间A"）
     * @return 匹配该位置的所有设备
     */
    QVector<Device> getDevicesByLocation(const QString &location);

private:
    QSqlDatabase m_db;  ///< SQLite数据库连接实例

    /**
     * @brief 初始化数据库表结构
     * @return 创建成功返回true
     */
    bool createTables();

    /**
     * @brief 执行SQL查询（内部方法）
     * @param query 已准备好的QSqlQuery对象
     * @return 执行成功返回true
     */
    bool executeQuery(QSqlQuery &query);

    /**
     * @brief 准备参数化查询（内部方法）
     * @param query 查询对象
     * @param sql SQL语句（带占位符如:param）
     * @param params 参数键值对（可选）
     * @return 准备成功返回true
     */
    bool prepareQuery(QSqlQuery &query, const QString &sql,
                     const QVariantMap &params = QVariantMap());
};

#endif // DATABASEDEVICE_H
