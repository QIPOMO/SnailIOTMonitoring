#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "admintitle.h"
#include "adminmessage.h"
#include "adminlayout.h"

namespace Ui {
class Admin;

}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

signals:
    void display(int);
    void displayclose(int);

private:
    Ui::Admin *ui;
    AdminTitle *m_pAdminTitle;
    AdminMessage *m_pAdminMessage;
    AdminLayout *m_pAdminLayout;

};

#endif // ADMIN_H
