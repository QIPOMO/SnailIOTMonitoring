#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QStringList>


class Serial : public QObject
{
    Q_OBJECT
public:
    // 串口配置结构体
    struct SerialConfig {
        QString portName;                   // 串口名称（如 "COM3" 或 "/dev/ttyUSB0"）
        qint32 baudRate = QSerialPort::Baud9600;  // 波特率（默认9600）
        QSerialPort::DataBits dataBits = QSerialPort::Data8;  // 数据位（默认8）
        QSerialPort::Parity parity = QSerialPort::NoParity;   // 校验位（默认无）
        QSerialPort::StopBits stopBits = QSerialPort::OneStop; // 停止位（默认1）
        QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl; // 流控（默认无）
    };

    explicit Serial(QObject *parent = nullptr);
    ~Serial();
    // 获取所有可用串口
    static QList<QSerialPortInfo> availablePorts();

    // 打开串口（使用默认配置）
    bool open(const QString &portName);

    // 打开串口（自定义配置）
    bool open(const SerialConfig &config);

    // 关闭串口
    void close();

    // 检查串口是否打开
    bool isOpen() const;

    // 读取数据（返回读取到的数据）
    QByteArray readAll();

    // 设置串口配置
    void setConfig(const SerialConfig &config);

signals:
    // 串口数据到达信号
    void dataReceived(const QByteArray &data);

    // 串口错误信号
    void errorOccurred(const QString &errorString);

private slots:
    // 内部槽函数：处理串口数据到达
    void onReadyRead();

    // 内部槽函数：处理串口错误
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serial;  // Qt串口对象
    SerialConfig m_config;  // 当前串口配置

};

#endif // SERIAL_H
