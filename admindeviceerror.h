#ifndef ADMINDEVICEERROR_H
#define ADMINDEVICEERROR_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include "serial.h"
#include <QDebug>


namespace Ui {
class adminDeviceError;
}

class adminDeviceError : public QWidget
{
    Q_OBJECT

public:
    explicit adminDeviceError(QWidget *parent = nullptr);
    ~adminDeviceError();
signals:
    void getSerial(const QByteArray &data);

public slots:
        void getmessage(const QByteArray &data);
        void updateMessage();  // 新增：定时更新消息的槽函数

private:
    Ui::adminDeviceError *ui;
    QTimer *m_timer;      // 新增：定时器对象
    QByteArray m_latestData; // 新增：缓存最新数据
};

#endif // ADMINDEVICEERROR_H
