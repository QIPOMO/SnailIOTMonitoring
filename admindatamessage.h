#ifndef ADMINDATAMESSAGE_H
#define ADMINDATAMESSAGE_H

#include <QWidget>
#include "databasedevice.h"
#include "databasestm.h"
#include "admindeviceerror.h"
#include <QtCharts>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QLineSeries>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTimer>


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class adminDataMessage;
}

class adminDataMessage : public QWidget
{
    Q_OBJECT

public:
    explicit adminDataMessage(QWidget *parent = nullptr);
    ~adminDataMessage();
    void shapeconfig();

signals:
    void getSerial(const QByteArray &data);

public slots:
        void getmessage(const QByteArray &data);
        void updateMessage();  // 新增：定时更新消息的槽函数
        void getMsg();


private:
    Ui::adminDataMessage *ui;
    databaseStm *dbStm;
    QTimer *m_timer;      // 新增：定时器对象
    QByteArray m_latestData; // 新增：缓存最新数据
    QChartView *chartView; // 图表视图
    QChart *chart;         // 图表对象
    QLineSeries *series;   // 折线系列

};

#endif // ADMINDATAMESSAGE_H
