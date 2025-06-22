#ifndef DEVICELAYOUT_H
#define DEVICELAYOUT_H

#include <QWidget>
#include <QStackedLayout>
#include "databasedevice.h"
#include "devicemanageruser.h"
#include "adddevice.h"
#include "admindeletedevice.h"

namespace Ui {
class DeviceLayout;
}

class DeviceLayout : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceLayout(QWidget *parent = nullptr);
    ~DeviceLayout();

signals:
    void display(int);
    void Device();

private:
    Ui::DeviceLayout *ui;
    QStackedLayout *m_pQStackedLayout;
    deviceManagerUser *m_pdeviceManagerUser;
    AddDevice *m_pAddDevice;
    adminDeleteDevice *m_padminDeleteDevice;

};

#endif // DEVICELAYOUT_H
