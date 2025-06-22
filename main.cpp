#include "mainwindows.h"

#include <QApplication>
#include "serial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindows w;
// 创建串口对象
    Serial serial;

    // 打印可用串口
    qDebug() << "Available ports:";
    for (const auto &port : Serial::availablePorts()) {
        qDebug() << port.portName();
    }

    // 配置串口
    Serial::SerialConfig config;
    config.portName = "COM3";  // 修改为你的串口
    config.baudRate = QSerialPort::Baud115200;

    // 打开串口
    if (serial.open(config)) {
        qDebug() << "Serial port opened successfully!";
        // 将Serial的信号连接到MainWindows的槽
        QObject::connect(&serial, &Serial::dataReceived, &w, &MainWindows::getSerial);
        QObject::connect(&serial, &Serial::errorOccurred, &w, &MainWindows::handleSerialError);
    } else {
        qDebug() << "Failed to open serial port!";
    }
    w.show();
    return a.exec();
}
