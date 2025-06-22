#include "databasedevice.h"

DatabaseDevice::DatabaseDevice(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "DEVICE_DB_CONNECTION");
}

DatabaseDevice::~DatabaseDevice()
{
    closeDatabase();
}

bool DatabaseDevice::openDatabase(const QString &databaseName)
{
    if(m_db.isOpen()) return true;

    m_db.setDatabaseName(databaseName);
    if(!m_db.open()) {
        qDebug() << "Cannot open database:" << m_db.lastError().text();
        return false;
    }

    return createTables();
}

void DatabaseDevice::closeDatabase()
{
    if(m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseDevice::isOpen() const
{
    return m_db.isOpen();
}

bool DatabaseDevice::createTables()
{
    QSqlQuery query(m_db);
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS devices (
            device_id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL UNIQUE,
            type TEXT NOT NULL,
            status TEXT NOT NULL,
            location TEXT NOT NULL,
            description TEXT,
            last_maintenance TEXT,
            created_at TEXT DEFAULT CURRENT_TIMESTAMP
        )
    )";

    return prepareQuery(query, sql);
}

bool DatabaseDevice::addDevice(const QString &name, const QString &type,
                             const QString &status, const QString &location,
                             const QString &description, const QDateTime &last_maintenance)
{
    QSqlQuery query(m_db);
    QString sql = R"(
        INSERT INTO devices (name, type, status, location, description, last_maintenance)
        VALUES (:name, :type, :status, :location, :description, :last_maintenance)
    )";

    QVariantMap params;
    params.insert(":name", name);
    params.insert(":type", type);
    params.insert(":status", status);
    params.insert(":location", location);
    params.insert(":description", description);
    params.insert(":last_maintenance", last_maintenance.toString(Qt::ISODate));

    return prepareQuery(query, sql, params);
}

bool DatabaseDevice::deleteDevice(int device_id)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "DELETE FROM devices WHERE device_id = :id",
                      {{":id", device_id}});
}

bool DatabaseDevice::deleteDeviceByName(const QString &name)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "DELETE FROM devices WHERE name = :name",
                      {{":name", name}});
}

// 更新设备名称
bool DatabaseDevice::updateDeviceName(int device_id, const QString &newName)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "UPDATE devices SET name = :name WHERE device_id = :id",
                      {{":name", newName}, {":id", device_id}});
}

// 更新设备类型
bool DatabaseDevice::updateDeviceType(int device_id, const QString &newType)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "UPDATE devices SET type = :type WHERE device_id = :id",
                      {{":type", newType}, {":id", device_id}});
}

// 更新设备状态
bool DatabaseDevice::updateDeviceStatus(int device_id, const QString &newStatus)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "UPDATE devices SET status = :status WHERE device_id = :id",
                      {{":status", newStatus}, {":id", device_id}});
}

// 更新设备位置
bool DatabaseDevice::updateDeviceLocation(int device_id, const QString &newLocation)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "UPDATE devices SET location = :location WHERE device_id = :id",
                      {{":location", newLocation}, {":id", device_id}});
}

// 更新设备描述
bool DatabaseDevice::updateDeviceDescription(int device_id, const QString &newDesc)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "UPDATE devices SET description = :desc WHERE device_id = :id",
                      {{":desc", newDesc}, {":id", device_id}});
}

// 更新最后维护时间
bool DatabaseDevice::updateLastMaintenance(int device_id, const QDateTime &newTime)
{
    QSqlQuery query(m_db);
    return prepareQuery(query, "UPDATE devices SET last_maintenance = :time WHERE device_id = :id",
                      {{":time", newTime.toString(Qt::ISODate)}, {":id", device_id}});
}



QVector<DatabaseDevice::Device> DatabaseDevice::getAllDevices()
{
    QVector<Device> devices;
    QSqlQuery query(m_db);

    if(prepareQuery(query, "SELECT * FROM devices ORDER BY device_id")) {
        while(query.next()) {
            Device device;
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.status = query.value("status").toString();
            device.location = query.value("location").toString();
            device.description = query.value("description").toString();
            device.last_maintenance = QDateTime::fromString(query.value("last_maintenance").toString(), Qt::ISODate);
            device.created_at = QDateTime::fromString(query.value("created_at").toString(), Qt::ISODate);

            devices.append(device);
        }
    }

    return devices;
}

DatabaseDevice::Device DatabaseDevice::getDeviceById(int device_id)
{
    Device device;
    QSqlQuery query(m_db);

    if(prepareQuery(query, "SELECT * FROM devices WHERE device_id = :id",
                   {{":id", device_id}}) && query.next()) {
        device.device_id = query.value("device_id").toInt();
        device.name = query.value("name").toString();
        device.type = query.value("type").toString();
        device.status = query.value("status").toString();
        device.location = query.value("location").toString();
        device.description = query.value("description").toString();
        device.last_maintenance = QDateTime::fromString(query.value("last_maintenance").toString(), Qt::ISODate);
        device.created_at = QDateTime::fromString(query.value("created_at").toString(), Qt::ISODate);
    }

    return device;
}

DatabaseDevice::Device DatabaseDevice::getDeviceByName(const QString &name)
{
    Device device;
    QSqlQuery query(m_db);

    if(prepareQuery(query, "SELECT * FROM devices WHERE name = :name",
                   {{":name", name}}) && query.next()) {
        device.device_id = query.value("device_id").toInt();
        device.name = query.value("name").toString();
        device.type = query.value("type").toString();
        device.status = query.value("status").toString();
        device.location = query.value("location").toString();
        device.description = query.value("description").toString();
        device.last_maintenance = QDateTime::fromString(query.value("last_maintenance").toString(), Qt::ISODate);
        device.created_at = QDateTime::fromString(query.value("created_at").toString(), Qt::ISODate);
    }

    return device;
}

QVector<DatabaseDevice::Device> DatabaseDevice::getDevicesByType(const QString &type)
{
    QVector<Device> devices;
    QSqlQuery query(m_db);

    if(prepareQuery(query, "SELECT * FROM devices WHERE type = :type ORDER BY device_id",
                   {{":type", type}})) {
        while(query.next()) {
            Device device;
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.status = query.value("status").toString();
            device.location = query.value("location").toString();
            device.description = query.value("description").toString();
            device.last_maintenance = QDateTime::fromString(query.value("last_maintenance").toString(), Qt::ISODate);
            device.created_at = QDateTime::fromString(query.value("created_at").toString(), Qt::ISODate);

            devices.append(device);
        }
    }

    return devices;
}

QVector<DatabaseDevice::Device> DatabaseDevice::getDevicesByStatus(const QString &status)
{
    QVector<Device> devices;
    QSqlQuery query(m_db);

    if(prepareQuery(query, "SELECT * FROM devices WHERE status = :status ORDER BY device_id",
                   {{":status", status}})) {
        while(query.next()) {
            Device device;
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.status = query.value("status").toString();
            device.location = query.value("location").toString();
            device.description = query.value("description").toString();
            device.last_maintenance = QDateTime::fromString(query.value("last_maintenance").toString(), Qt::ISODate);
            device.created_at = QDateTime::fromString(query.value("created_at").toString(), Qt::ISODate);

            devices.append(device);
        }
    }

    return devices;
}

QVector<DatabaseDevice::Device> DatabaseDevice::getDevicesByLocation(const QString &location)
{
    QVector<Device> devices;
    QSqlQuery query(m_db);

    if(prepareQuery(query, "SELECT * FROM devices WHERE location = :location ORDER BY device_id",
                   {{":location", location}})) {
        while(query.next()) {
            Device device;
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.status = query.value("status").toString();
            device.location = query.value("location").toString();
            device.description = query.value("description").toString();
            device.last_maintenance = QDateTime::fromString(query.value("last_maintenance").toString(), Qt::ISODate);
            device.created_at = QDateTime::fromString(query.value("created_at").toString(), Qt::ISODate);

            devices.append(device);
        }
    }

    return devices;
}

bool DatabaseDevice::executeQuery(QSqlQuery &query)
{
    if(!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseDevice::prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params)
{
    if(!query.prepare(sql)) {
        qDebug() << "Prepare failed:" << query.lastError().text();
        return false;
    }

    for(auto it = params.begin(); it != params.end(); ++it) {
        query.bindValue(it.key(), it.value());
    }

    return executeQuery(query);
}
