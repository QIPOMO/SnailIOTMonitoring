#include "admindeviceerror.h"
#include "ui_admindeviceerror.h"


adminDeviceError::adminDeviceError(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDeviceError),
    m_timer(new QTimer(this)){
    ui->setupUi(this);

    // 连接串口数据信号
    connect(this, &adminDeviceError::getSerial, this, &adminDeviceError::getmessage);

    // 定时器连接：无参槽函数
    connect(m_timer, &QTimer::timeout, this, &adminDeviceError::updateMessage);
    m_timer->setInterval(2000);  // 先设置间隔
    m_timer->start();           // 无参启动
}


void adminDeviceError::getmessage(const QByteArray &data) {
    m_latestData = data;
    QString max = ui->MAX->text();
    QString min = ui->MIN->text();
    ui->Message->clear();
    if(m_latestData >= max || m_latestData <= min){
        ui->Message->setText(QString::fromUtf8(m_latestData)); // 实时更新最新数据
        ui->Messages->append("=============================");
        ui->Messages->append(QString::fromUtf8(m_latestData));   // 追加到历史记录
        ui->Messages->append("=============================");
        //qDebug()<<"警告，数据超过设置的阈值";
    }else {
        ui->Message->setText(QString::fromUtf8(m_latestData));    // 实时更新最新数据
        ui->Messages->append(QString::fromUtf8(m_latestData));   // 追加到历史记录
    }
}

void adminDeviceError::updateMessage() {
    if (!m_latestData.isEmpty()) {
        ui->Message->setText(QString::fromUtf8(m_latestData)); // 定时强制刷新（防数据残留）
    }
}

adminDeviceError::~adminDeviceError(){
    m_timer->stop();  // 停止定时器
    delete m_timer;   // 释放内存
    delete ui;
}
