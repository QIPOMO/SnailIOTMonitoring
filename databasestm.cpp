#include "databasestm.h"

databaseStm::databaseStm(QObject *parent) : QObject(parent) {

}

databaseStm::~databaseStm()
{
    closeDatabase();
}

bool databaseStm::openDatabase(const QString &databaseName)
{

    if (m_db.isOpen()) {
        return true;
    }

    // 1. 检查驱动是否可用
      if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
          qCritical() << "SQLite驱动不可用";
          return false;
      }


    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(databaseName);
    // 确保数据库连接使用UTF-8编码
       QSqlQuery query(m_db);
       query.exec("PRAGMA encoding = \"UTF-8\"");

    if (!m_db.open()) {
        qDebug() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    // 启用外键约束
    QSqlQuery("PRAGMA foreign_keys = ON", m_db);

    return createTables();
}

void databaseStm::closeDatabase()
{

    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool databaseStm::isOpen() const
{
    return m_db.isOpen();
}

bool databaseStm::createTables()
{

    if (!isOpen()) return false;

    QSqlQuery query(m_db);

    // 创建data表(传感器数据表)
     QString createDataTable =
         "CREATE TABLE IF NOT EXISTS data ("
         "data_id INTEGER PRIMARY KEY AUTOINCREMENT, "
         "device_id INTEGER NOT NULL, "
         "timestamp DATETIME NOT NULL, "
         "temperature REAL, "
         "humidity REAL, "
         "light REAL, "
         "co2 REAL, "
         "pressure REAL, "
         "FOREIGN KEY(device_id) REFERENCES devices(device_id) ON DELETE CASCADE)";

     if (!query.exec(createDataTable)) {
         qDebug() << "Failed to create data table:" << query.lastError().text();
         return false;
     }

     query.exec("SELECT name FROM sqlite_master WHERE type='table'");
     while (query.next()) {
         qDebug() << "Table found:" << query.value(0).toString();
     }

     if(query.exec("SELECT COUNT(*) FROM data")) {
         if(query.next()) {
             qDebug() << "Data table has" << query.value(0).toInt() << "rows";
         }
     }

     // 创建索引
     QStringList indexQueries = {
         "CREATE INDEX IF NOT EXISTS idx_data_device ON data(device_id)",
         "CREATE INDEX IF NOT EXISTS idx_data_timestamp ON data(timestamp)"
     };

     for (const QString &sql : indexQueries) {
         if (!query.exec(sql)) {
             qDebug() << "Failed to create index:" << query.lastError().text();
         }
     }
     return true;
 }

bool databaseStm::executeQuery(QSqlQuery &query) const
{
    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text();
        qDebug() << "Executed SQL:" << query.lastQuery();
        return false;
    }
    return true;
}

bool databaseStm::prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params) const
{
    if (!query.prepare(sql)) {
        qWarning() << "Prepare error:" << query.lastError().text();
        return false;
    }

    for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
        query.bindValue(it.key(), it.value());
    }

    return executeQuery(query);
}

bool databaseStm::insertData(const Data &data)
{
    if (!isOpen()) return false;

    // 1. 验证设备是否存在
    QSqlQuery checkQuery(m_db);
    checkQuery.prepare("SELECT 1 FROM devices WHERE device_id = ?");
    checkQuery.addBindValue(data.device_id);

    if (!checkQuery.exec() || !checkQuery.next()) {
        qWarning() << "设备ID" << data.device_id << "不存在，无法插入数据";
        return false;
    }


    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", data.device_id);
    params.insert(":timestamp", data.timestamp);
    params.insert(":temperature", data.temperature);
    params.insert(":humidity", data.humidity);
    params.insert(":light", data.light);
    params.insert(":co2", data.co2);
    params.insert(":pressure", data.pressure);

    return prepareQuery(query,
                      "INSERT INTO data (device_id, timestamp, temperature, humidity, light, co2, pressure) "
                      "VALUES (:device_id, :timestamp, :temperature, :humidity, :light, :co2, :pressure)",
                      params);
}

QVector<databaseStm::Data> databaseStm::getDataByDevice(int device_id, int limit) const
{
    QVector<Data> results;
    if (!isOpen()) return results;

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":device_id", device_id);
    params.insert(":limit", limit);

    if (prepareQuery(query,
                    "SELECT data_id, device_id, timestamp, temperature, humidity, light, co2, pressure "
                    "FROM data WHERE device_id = :device_id ORDER BY timestamp DESC LIMIT :limit",
                    params)) {
        while (query.next()) {
            Data data;
            data.data_id = query.value("data_id").toInt();
            data.device_id = query.value("device_id").toInt();
            data.timestamp = query.value("timestamp").toDateTime();
            data.temperature = query.value("temperature").toFloat();
            data.humidity = query.value("humidity").toFloat();
            data.light = query.value("light").toFloat();
            data.co2 = query.value("co2").toFloat();
            data.pressure = query.value("pressure").toFloat();
            results.append(data);
        }
    }

    return results;
}

QVector<databaseStm::Data> databaseStm::getDataByTimeRange(const QDateTime &start, const QDateTime &end) const{
    QVector<Data> result;

       // 检查数据库是否已打开
       if (!isOpen()) {
           qDebug() << "数据库未打开，无法查询数据";
           return result;
       }

       // 创建查询对象
       QSqlQuery query(m_db);

       // 准备SQL查询语句，使用参数化查询防止SQL注入
       query.prepare(
           "SELECT data_id, device_id, timestamp, temperature, humidity, light, co2, pressure "
           "FROM data "
           "WHERE timestamp BETWEEN :start AND :end "
           "ORDER BY timestamp ASC"
       );

       // 绑定查询参数
       query.bindValue(":start", start.toString(Qt::ISODate));
       query.bindValue(":end", end.toString(Qt::ISODate));

       // 执行查询
       if (!query.exec()) {
           qDebug() << "查询数据失败:" << query.lastError().text();
           return result;
       }

       // 处理查询结果
       while (query.next()) {
           Data data;

           // 从查询结果中提取数据并填充到Data结构体
           data.data_id = query.value("data_id").toInt();
           data.device_id = query.value("device_id").toInt();
           data.timestamp = QDateTime::fromString(query.value("timestamp").toString(), Qt::ISODate);
           data.temperature = query.value("temperature").toDouble();
           data.humidity = query.value("humidity").toDouble();
           data.light = query.value("light").toDouble();
           data.co2 = query.value("co2").toDouble();
           data.pressure = query.value("pressure").toDouble();

           // 将数据添加到结果向量
           result.append(data);
       }

       qDebug() << "查询到" << result.size() << "条数据记录";
       return result;
}

/**
 * @brief 获取温度时间序列数据
 * @param device_id 设备ID（-1表示所有设备）
 * @param start 起始时间
 * @param end 结束时间
 * @return QVector<QPair<QDateTime, double>> 时间-温度对
 */



bool databaseStm::deleteOldData(int daysToKeep)
{

    if (!isOpen()) return false;

    QDateTime cutoff = QDateTime::currentDateTime().addDays(-daysToKeep);

    QSqlQuery query(m_db);
    QVariantMap params;
    params.insert(":cutoff", cutoff);

    return prepareQuery(query,
                      "DELETE FROM data WHERE timestamp < :cutoff",
                      params);
}



