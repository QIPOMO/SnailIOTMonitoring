#ifndef DEVICEMESSAGE_H
#define DEVICEMESSAGE_H

#include <QWidget>

namespace Ui {
class DeviceMessage;
}

class DeviceMessage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceMessage(QWidget *parent = nullptr);
    ~DeviceMessage();

signals:
    void display(int);

private:
    Ui::DeviceMessage *ui;
};

#endif // DEVICEMESSAGE_H
