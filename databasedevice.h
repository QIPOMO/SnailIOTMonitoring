// databasedevice.h
#ifndef DATABASEDEVICE_H
#define DATABASEDEVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QDateTime>

class DatabaseDevice : public QObject
{
    Q_OBJECT
public:
    struct Device {
        int device_id;
        QString name;
        QString type;
        QString location;
        QString manufacturer;
        QString model;
        QDateTime installation_date;
    };

    // 获取单例实例
    static DatabaseDevice* instance();

    // 禁止拷贝和赋值
    DatabaseDevice(const DatabaseDevice&) = delete;
    DatabaseDevice& operator=(const DatabaseDevice&) = delete;

    bool openDatabase(const QString &databaseName = "devices.db");
    void closeDatabase();
    bool isOpen() const;

    bool addDevice(const QString &name, const QString &type,
                  const QString &location, const QString &manufacturer = "",
                  const QString &model = "", const QDateTime &installationDate = QDateTime());
    bool deleteDevice(int device_id);
    bool deleteDeviceByName(const QString &name);
    bool updateDeviceName(int device_id, const QString &newName);
    bool updateDeviceType(int device_id, const QString &newType);
    bool updateDeviceLocation(int device_id, const QString &newLocation);
    bool updateDeviceManufacturer(int device_id, const QString &newManufacturer);
    bool updateDeviceModel(int device_id, const QString &newModel);
    bool updateDeviceInstallationDate(int device_id, const QDateTime &newDate);
    bool deviceExists(int device_id) const;
    bool deviceExists(const QString &name) const;
    QVector<Device> getAllDevices() const;
    Device getDeviceById(int device_id) const;
    Device getDeviceByName(const QString &name) const;
    QVector<Device> getDevicesByType(const QString &type) const;
    QVector<Device> getDevicesByLocation(const QString &location) const;

private:
    // 私有构造函数
    explicit DatabaseDevice(QObject *parent = nullptr);
    ~DatabaseDevice();

    static DatabaseDevice* m_instance;
    static QMutex m_mutex;

    QSqlDatabase m_db;
    mutable QMutex m_dbMutex;

    bool createTables();
    bool executeQuery(QSqlQuery &query) const;
    bool prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params = QVariantMap()) const;
};

#endif // DATABASEDEVICE_H
