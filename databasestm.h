#ifndef DATABASESTM_H
#define DATABASESTM_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QVector>
#include <QDebug>
#include <QTimer>


class databaseStm : public QObject
{
    Q_OBJECT
public:
    explicit databaseStm(QObject *parent = nullptr);
    ~databaseStm();

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
    struct Data {
        int data_id;                ///< 数据ID，主键
        int device_id;              ///< 设备ID,外键
        QDateTime timestamp;        //// 时间戳
        double temperature;        ///< 温度
        double humidity;           ///< 湿度
        double light;              ///< 光照强度
        double co2;                ///< 二氧化碳浓度
        double pressure;           ///< 气压
    };

    /**
     * @brief 插入传感器数据记录
     * @param data 包含设备ID、时间戳及各传感器值的Data结构体
     * @return 成功返回true，失败返回false并输出错误日志
     * @note 会自动检查外键约束，确保device_id在devices表中存在
     */
    bool insertData(const Data &data);
    /**
     * @brief 根据data_id删除单条数据记录
     * @param data_id 要删除的数据记录ID
     * @return 成功返回true，失败返回false
     * @warning 此操作不可逆，请谨慎使用
     */
    bool deleteData(int data_id);
    /**
     * @brief 获取指定设备的最新数据记录
     * @param device_id 设备ID
     * @param limit 返回记录数限制(默认100条)
     * @return 包含Data对象的QVector，按时间戳降序排列
     * @note 如果设备不存在或没有数据，返回空QVector
     */
    QVector<Data> getDataByDevice(int device_id, int limit = 100) const;
    /**
     * @brief 获取指定时间范围内的所有数据记录
     * @param start 起始时间
     * @param end 结束时间
     * @return 包含Data对象的QVector，按时间戳升序排列
     * @note 时间范围包含边界值(start <= timestamp <= end)
     */
    QVector<Data> getDataByTimeRange(const QDateTime &start, const QDateTime &end) const;
    /**
     * @brief 删除指定天数前的旧数据
     * @param daysToKeep 要保留数据的天数(早于此天数的数据将被删除)
     * @return 成功返回true，失败返回false
     * @example deleteOldData(30) // 保留最近30天数据
     */
    bool deleteOldData(int daysToKeep);

    QVector<QPair<QDateTime, double>> getTemperatureSeries(int device_id,
                                      const QDateTime &start = QDateTime(),
                                      const QDateTime &end = QDateTime::currentDateTime()) const;

private:
    // 创建表结构
    bool createTables();
    // 执行SQL查询
    bool executeQuery(QSqlQuery &query) const;
    // 准备参数化查询
    bool prepareQuery(QSqlQuery &query, const QString &sql, const QVariantMap &params = QVariantMap()) const;

    QSqlDatabase m_db;

};

#endif // DATABASESTM_H
