#include "admindatamessage.h"
#include "ui_admindatamessage.h"
#include <QMessageBox>
#include <QStandardItemModel>

adminDataMessage::adminDataMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDataMessage),
    dbStm(new databaseStm(this)),
    m_timer(new QTimer(this)){
    ui->setupUi(this);
    shapeconfig();


    // 连接串口数据信号
    connect(this, &adminDataMessage::getSerial, this, &adminDataMessage::getmessage);
    //connect(this, &adminDataMessage::getSerial, this, &adminDataMessage::shapeconfig);
    connect(ui->pushButton,&QPushButton::clicked,this,&adminDataMessage::getMsg);
    // 定时器连接：无参槽函数
    connect(m_timer, &QTimer::timeout, this, &adminDataMessage::updateMessage);
    m_timer->setInterval(5000);  // 先设置间隔
    m_timer->start();           // 无参启动

}

void adminDataMessage::getmessage(const QByteArray &data) {
    // 先解析JSON数据
        QJsonParseError error;
        //QString jsonString = QString::fromUtf8(data); // 确保使用UTF-8
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);

        if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON解析错误:" << error.errorString();
            return;
        }

        QJsonObject json = doc.object();
        databaseStm stm;

        if(!stm.openDatabase()){
            stm.closeDatabase();
            return;
        }

        databaseStm::Data messagedata;

        messagedata.device_id = json["device_id"].toInt(); // 从JSON获取设备ID
        messagedata.timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
        messagedata.temperature = json["temperature"].toDouble();
        messagedata.humidity = json["humidity"].toDouble();
        messagedata.light = json["light"].toDouble();
        messagedata.co2 = json["co2"].toDouble();
        messagedata.pressure = json["pressure"].toDouble();

        if(stm.insertData(messagedata)){
            qDebug() << "数据插入成功，设备ID:" << messagedata.device_id;
        } else {
            QMessageBox::warning(this, "警告", "数据插入失败", QMessageBox::Ok);
            qDebug() << "数据插入失败";
        }
        stm.closeDatabase();
}

void adminDataMessage::updateMessage() {
    if (!m_latestData.isEmpty()) {

    }
}

void adminDataMessage::getMsg() {

    QDateTime startime = ui->dateTimeEditStart->dateTime();
    QDateTime stoptime = ui->dateTimeEditStop->dateTime();

    databaseStm stm;
    if(!stm.openDatabase()) {
        stm.closeDatabase();
        return;
    }

    // 获取数据 (注意这里需要QDateTime而不是QTime)
    QVector<databaseStm::Data> dataList = stm.getDataByTimeRange(startime, stoptime);

    // 创建模型
    QStandardItemModel *model = new QStandardItemModel(this);

    // 设置表头
    model->setHorizontalHeaderLabels(QStringList()
        << "ID"
        << "设备ID"
        << "时间"
        << "温度"
        << "湿度"
        << "光照"
        << "CO2"
        << "气压");

    // 循环添加数据
    for (const databaseStm::Data &data : dataList) {
        QList<QStandardItem*> rowItems;

        rowItems.append(new QStandardItem(QString::number(data.data_id)));
        rowItems.append(new QStandardItem(QString::number(data.device_id)));
        rowItems.append(new QStandardItem(data.timestamp.toString("yyyy-MM-dd hh:mm:ss")));
        rowItems.append(new QStandardItem(QString::number(data.temperature)));
        rowItems.append(new QStandardItem(QString::number(data.humidity)));
        rowItems.append(new QStandardItem(QString::number(data.light)));
        rowItems.append(new QStandardItem(QString::number(data.co2)));
        rowItems.append(new QStandardItem(QString::number(data.pressure)));

        model->appendRow(rowItems);
    }
    // 设置到视图
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 禁止编辑
}

void adminDataMessage::shapeconfig() {

    // 先解析JSON数据
       // QJsonParseError error;
        //QString jsonString = QString::fromUtf8(data); // 确保使用UTF-8
        //QJsonDocument doc = QJsonDocument::fromJson(data, &error);

//        if (error.error != QJsonParseError::NoError) {
//            qDebug() << "JSON解析错误:" << error.errorString();
//            return;
//        }

//        QJsonObject json = doc.object();

//        databaseStm stm;

//        if(!stm.openDatabase()){
//            stm.closeDatabase();
//            return;
//        }

//        int device_id = json["device_id"].toInt(); // 从JSON获取设备ID
//        QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
//        double temperature = json["temperature"].toDouble();



    // 1. 创建图表
        chart = new QChart();
        chart->setTitle("传感器数据趋势图");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // 2. 创建折线系列
        series = new QLineSeries();
        series->setName("温度(°C)");

        // 3. 添加数据（示例数据）
        series->append(0, 23.5);
        series->append(1, 24.1);
        series->append(2, 25.3);
        series->append(3, 22.7);
        series->append(4, 21.9);

        // 4. 将系列添加到图表
        chart->addSeries(series);

        // 5. 创建坐标轴
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("时间序列");
        axisX->setLabelFormat("%d");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("温度值");
        axisY->setLabelFormat("%.1f");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        // 6. 创建图表视图并嵌入UI
        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        if (!ui->chartWidget->layout()) {
            ui->chartWidget->setLayout(new QVBoxLayout());
            ui->chartWidget->layout()->setContentsMargins(0, 0, 0, 0);
        }
        ui->chartWidget->layout()->addWidget(chartView);

}


adminDataMessage::~adminDataMessage() {
    delete ui;
    delete m_timer;   // 释放内存
}


