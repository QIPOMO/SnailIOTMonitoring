#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include "login.h"
#include "newuser.h"
#include "admin.h"
#include "user.h"
#include "forgotpassword.h"
#include "titlebar.h"
#include "statusbar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedLayout *m_pQStackedLayout;
    Login *m_pLogin;
    NewUser *m_pNewUser;
    Admin *m_pAdmin;
    User *m_pUser;
    ForgotPassword *m_pForgotPassword;
    Titlebar *m_pTitlebar;
    Statusbar *m_pStatusbar;
};
#endif // MAINWINDOW_H
