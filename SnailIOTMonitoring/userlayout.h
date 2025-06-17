#ifndef USERLAYOUT_H
#define USERLAYOUT_H

#include <QWidget>
#include <QStackedLayout>
#include "getuserall.h"
#include "changeuser.h"
#include "devicemanageruser.h"

namespace Ui {
class UserLayout;
}

class UserLayout : public QWidget
{
    Q_OBJECT

public:
    explicit UserLayout(QWidget *parent = nullptr);
    ~UserLayout();

signals:
    void display(int);
    void Loginame(const QString &);

private:
    Ui::UserLayout *ui;
    QStackedLayout *m_pQStackedLayout;
    getUserAll *m_pgetUserAll;
    changeUser *m_pchangeUser;
    deviceManagerUser *m_pdeviceManagerUser;

};

#endif // USERLAYOUT_H
