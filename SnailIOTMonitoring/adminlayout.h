#ifndef ADMINLAYOUT_H
#define ADMINLAYOUT_H

#include <QWidget>
#include <QStackedLayout>
#include "admingetuserall.h"
#include "adminchangepassword.h"

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

private:
    Ui::AdminLayout *ui;
    QStackedLayout *m_pQStackedLayout;
    adminGetUserAll *m_padminGetUserAll;
    adminChangePassword *m_padminChangePassword;

};

#endif // ADMINLAYOUT_H
