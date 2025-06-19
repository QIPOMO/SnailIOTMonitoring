#include "databasedevice.h"

// 初始化静态成员
DatabaseDevice* DatabaseDevice::m_instance = nullptr;
QMutex DatabaseDevice::m_mutex;

DatabaseDevice* DatabaseDevice::instance()
{
    QMutexLocker locker(&m_mutex);
    if (!m_instance) {
        m_instance = new DatabaseDevice();
    }
    return m_instance;
}

DatabaseDevice::DatabaseDevice(QObject *parent) : QObject(parent)
{
    // 初始化时不打开数据库，需要显式调用openDatabase
}

DatabaseDevice::~DatabaseDevice()
{
    closeDatabase();
}

bool DatabaseDevice::openDatabase(const QString &databaseName)
{
    QMutexLocker locker(&m_dbMutex);

    if (m_db.isOpen()) {
        return true;
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE", "device_connection");
    m_db.setDatabaseName(databaseName);

    if (!m_db.open()) {
        qDebug() << "Error: Could not open device database:" << m_db.lastError().text();
        return false;
    }

    return createTables();
}

void DatabaseDevice::closeDatabase()
{
    QMutexLocker locker(&m_dbMutex);
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseDevice::isOpen() const
{
    QMutexLocker locker(&m_dbMutex);
    return m_db.isOpen();
}

bool DatabaseDevice::createTables()
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QString sql =
        "CREATE TABLE IF NOT EXISTS devices ("
        "device_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "location TEXT NOT NULL, "
        "manufacturer TEXT, "
        "model TEXT, "
        "installation_date TEXT)";

    if (!query.prepare(sql) || !query.exec()) {
        qDebug() << "Error creating devices table:" << query.lastError().text();
        return false;
    }

    // 创建索引提高查询性能
    QStringList indexQueries = {
        "CREATE INDEX IF NOT EXISTS idx_devices_name ON devices(name)",
        "CREATE INDEX IF NOT EXISTS idx_devices_type ON devices(type)",
        "CREATE INDEX IF NOT EXISTS idx_devices_location ON devices(location)"
    };

    for (const QString &indexSql : indexQueries) {
        if (!query.exec(indexSql)) {
            qDebug() << "Error creating index:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

bool DatabaseDevice::executeQuery(QSqlQuery &query) const
{
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        qDebug() << "Executed SQL:" << query.lastQuery();
        return false;
    }
    return true;
}

bool DatabaseDevice::prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params) const
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

bool DatabaseDevice::addDevice(const QString &name, const QString &type,
                             const QString &location, const QString &manufacturer,
                             const QString &model, const QDateTime &installationDate)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    // 参数验证
    if (name.isEmpty() || type.isEmpty() || location.isEmpty()) {
        qDebug() << "Error: Device name, type and location are required";
        return false;
    }

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);
    params.insert(":type", type);
    params.insert(":location", location);
    params.insert(":manufacturer", manufacturer);
    params.insert(":model", model);
    params.insert(":date", installationDate.toString(Qt::ISODate));

    return prepareQuery(query,
                      "INSERT INTO devices (name, type, location, manufacturer, model, installation_date) "
                      "VALUES (:name, :type, :location, :manufacturer, :model, :date)",
                      params);
}

bool DatabaseDevice::deleteDevice(int device_id)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);

    return prepareQuery(query,
                       "DELETE FROM devices WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::deleteDeviceByName(const QString &name)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    return prepareQuery(query,
                       "DELETE FROM devices WHERE name = :name",
                       params);
}

bool DatabaseDevice::updateDeviceName(int device_id, const QString &newName)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen() || newName.isEmpty()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":name", newName);

    return prepareQuery(query,
                       "UPDATE devices SET name = :name WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::updateDeviceType(int device_id, const QString &newType)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen() || newType.isEmpty()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":type", newType);

    return prepareQuery(query,
                       "UPDATE devices SET type = :type WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::updateDeviceLocation(int device_id, const QString &newLocation)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen() || newLocation.isEmpty()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":location", newLocation);

    return prepareQuery(query,
                       "UPDATE devices SET location = :location WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::updateDeviceManufacturer(int device_id, const QString &newManufacturer)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":manufacturer", newManufacturer);

    return prepareQuery(query,
                       "UPDATE devices SET manufacturer = :manufacturer WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::updateDeviceModel(int device_id, const QString &newModel)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":model", newModel);

    return prepareQuery(query,
                       "UPDATE devices SET model = :model WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::updateDeviceInstallationDate(int device_id, const QDateTime &newDate)
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen() || !newDate.isValid()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":date", newDate.toString(Qt::ISODate));

    return prepareQuery(query,
                       "UPDATE devices SET installation_date = :date WHERE device_id = :device_id",
                       params);
}

bool DatabaseDevice::deviceExists(int device_id) const
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);

    if (!prepareQuery(query,
                     "SELECT COUNT(*) FROM devices WHERE device_id = :device_id",
                     params)) {
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool DatabaseDevice::deviceExists(const QString &name) const
{
    QMutexLocker locker(&m_dbMutex);
    if (!isOpen() || name.isEmpty()) return false;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    if (!prepareQuery(query,
                     "SELECT COUNT(*) FROM devices WHERE name = :name",
                     params)) {
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

QVector<DatabaseDevice::Device> DatabaseDevice::getAllDevices() const
{
    QMutexLocker locker(&m_dbMutex);
    QVector<Device> devices;
    if (!isOpen()) return devices;

    QSqlQuery query("SELECT device_id, name, type, location, manufacturer, model, installation_date FROM devices", m_db);
    while (query.next()) {
        Device device;
        device.device_id = query.value("device_id").toInt();
        device.name = query.value("name").toString();
        device.type = query.value("type").toString();
        device.location = query.value("location").toString();
        device.manufacturer = query.value("manufacturer").toString();
        device.model = query.value("model").toString();
        device.installation_date = query.value("installation_date").toDateTime();
        devices.append(device);
    }

    return devices;
}

DatabaseDevice::Device DatabaseDevice::getDeviceById(int device_id) const
{
    QMutexLocker locker(&m_dbMutex);
    Device device;
    if (!isOpen()) return device;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);

    if (prepareQuery(query,
                    "SELECT device_id, name, type, location, manufacturer, model, installation_date "
                    "FROM devices WHERE device_id = :device_id",
                    params)) {
        if (query.next()) {
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.location = query.value("location").toString();
            device.manufacturer = query.value("manufacturer").toString();
            device.model = query.value("model").toString();
            device.installation_date = query.value("installation_date").toDateTime();
        }
    }

    return device;
}

DatabaseDevice::Device DatabaseDevice::getDeviceByName(const QString &name) const
{
    QMutexLocker locker(&m_dbMutex);
    Device device;
    if (!isOpen() || name.isEmpty()) return device;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":name", name);

    if (prepareQuery(query,
                     "SELECT device_id, name, type, location, manufacturer, model, installation_date "
                     "FROM devices WHERE name = :name",
                    params)) {
        if (query.next()) {
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.location = query.value("location").toString();
            device.manufacturer = query.value("manufacturer").toString();
            device.model = query.value("model").toString();
            device.installation_date = query.value("installation_date").toDateTime();
        }
    }
    return device;
}

QVector<DatabaseDevice::Device> DatabaseDevice::getDevicesByType(const QString &type) const
{
    QMutexLocker locker(&m_dbMutex);
    QVector<Device> devices;
    if (!isOpen() || type.isEmpty()) return devices;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":type", type);

    if (prepareQuery(query,
                     "SELECT device_id, name, type, location, manufacturer, model, installation_date "
                     "FROM devices WHERE type = :type",
                    params)) {
        while (query.next()) {
            Device device;
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.location = query.value("location").toString();
            device.manufacturer = query.value("manufacturer").toString();
            device.model = query.value("model").toString();
            device.installation_date = query.value("installation_date").toDateTime();
            devices.append(device);
        }
    }
    return devices;
}

QVector<DatabaseDevice::Device> DatabaseDevice::getDevicesByLocation(const QString &location) const
{
    QMutexLocker locker(&m_dbMutex);
    QVector<Device> devices;
    if (!isOpen() || location.isEmpty()) return devices;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":location", location);

    if (prepareQuery(query,
                     "SELECT device_id, name, type, location, manufacturer, model, installation_date "
                     "FROM devices WHERE location = :location",
                    params)) {
        while (query.next()) {
            Device device;
            device.device_id = query.value("device_id").toInt();
            device.name = query.value("name").toString();
            device.type = query.value("type").toString();
            device.location = query.value("location").toString();
            device.manufacturer = query.value("manufacturer").toString();
            device.model = query.value("model").toString();
            device.installation_date = query.value("installation_date").toDateTime();
            devices.append(device);
        }
    }
    return devices;
}
