#ifndef ADMINDEVICEMESSAGE_H
#define ADMINDEVICEMESSAGE_H

#include <QWidget>
#include "devicemessage.h"
#include "devicelayout.h"

namespace Ui {
class adminDeviceMessage;
}

class adminDeviceMessage : public QWidget
{
    Q_OBJECT

public:
    explicit adminDeviceMessage(QWidget *parent = nullptr);
    ~adminDeviceMessage();

private:
    Ui::adminDeviceMessage *ui;
    DeviceMessage *m_pDeviceMessage;
    DeviceLayout *m_pDeviceLayout;


};

#endif // ADMINDEVICEMESSAGE_H
