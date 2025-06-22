#include "serial.h"
#include <QDebug>

Serial::Serial(QObject *parent) : QObject(parent) {
    m_serial = new QSerialPort(this);

    // 连接信号槽
    connect(m_serial, &QSerialPort::readyRead, this, &Serial::onReadyRead);
    connect(m_serial, &QSerialPort::errorOccurred, this, &Serial::onErrorOccurred);
}

// 获取所有可用串口
QList<QSerialPortInfo> Serial::availablePorts()
{
    return QSerialPortInfo::availablePorts();
}

// 打开串口（默认配置）
bool Serial::open(const QString &portName)
{
    m_config.portName = portName;
    return open(m_config);
}

// 打开串口（自定义配置）
bool Serial::open(const SerialConfig &config)
{
    if (m_serial->isOpen()) {
        qWarning() << "Serial port is already open!";
        return false;
    }

    m_config = config;
    m_serial->setPortName(m_config.portName);
    m_serial->setBaudRate(m_config.baudRate);
    m_serial->setDataBits(m_config.dataBits);
    m_serial->setParity(m_config.parity);
    m_serial->setStopBits(m_config.stopBits);
    m_serial->setFlowControl(m_config.flowControl);

    if (!m_serial->open(QIODevice::ReadWrite)) {
        qWarning() << "Failed to open serial port:" << m_serial->errorString();
        return false;
    }

    qDebug() << "Serial port opened successfully:" << m_config.portName;
    return true;
}

// 关闭串口
void Serial::close()
{
    if (m_serial->isOpen()) {
        m_serial->close();
        qDebug() << "Serial port closed:" << m_config.portName;
    }
}

// 检查串口是否打开
bool Serial::isOpen() const
{
    return m_serial->isOpen();
}


// 读取数据
QByteArray Serial::readAll()
{
    if (!m_serial->isOpen()) {
        qWarning() << "Serial port is not open!";
        return QByteArray();
    }

    return m_serial->readAll();
}

// 设置串口配置
void Serial::setConfig(const SerialConfig &config)
{
    if (m_serial->isOpen()) {
        qWarning() << "Cannot change config while port is open!";
        return;
    }

    m_config = config;
}

// 槽函数：处理串口数据到达
void Serial::onReadyRead()
{
    QByteArray data = m_serial->readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);  // 发出数据到达信号
        qDebug() << "Data received:" << data.toHex();
    }
}

// 槽函数：处理串口错误
void Serial::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        QString errorStr = m_serial->errorString();
        qWarning() << "Serial port error:" << errorStr;
        emit errorOccurred(errorStr);  // 发出错误信号
    }
}

Serial::~Serial() {
    close();
    delete m_serial;
}
