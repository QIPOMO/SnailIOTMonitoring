#ifndef ADMINLAYOUT_H
#define ADMINLAYOUT_H

#include <QWidget>
#include <QStackedLayout>
#include "admingetuserall.h"
#include "adminchangepassword.h"
#include "admindevicemessage.h"
#include "admindeviceerror.h"
#include "admindatamessage.h"
#include "admindataanalysis.h"
#include "admindeleteuser.h"
#include "adminloginmessage.h"

namespace Ui {
class AdminLayout;
}

class AdminLayout : public QWidget
{
    Q_OBJECT

public:
    explicit AdminLayout(QWidget *parent = nullptr);
    ~AdminLayout();
signals:
    void display(int);
    void getSerial(const QByteArray &data);

private:
    Ui::AdminLayout *ui;
    QStackedLayout *m_pQStackedLayout;
    adminGetUserAll *m_padminGetUserAll;
    adminChangePassword *m_padminChangePassword;
    adminDeviceMessage *m_padminDeviceMessage;
    adminDeviceError *m_padminDeviceError;
    adminDataMessage *m_padminDataMessage;
    adminDataAnalysis *m_padminDataAnalysis;
    adminDeleteUser *m_padminDeleteUser;
    adminLoginMessage *m_padminLoginMessage;
};

#endif // ADMINLAYOUT_H
