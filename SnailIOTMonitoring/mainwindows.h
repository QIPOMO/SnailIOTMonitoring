#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QWidget>
#include <QStackedLayout>
#include "login.h"
#include "titlebar.h"
#include "statusbar.h"
#include "basecenter.h"
#include "centerbar.h"


namespace Ui {
class MainWindows;
}

class MainWindows : public BaseCenter
{
    Q_OBJECT

public:
    explicit MainWindows(QWidget *parent = nullptr);
    ~MainWindows();

private:
    Ui::MainWindows *ui;
    Login *m_pLogin;
    Titlebar *m_pTitlebar;
    Statusbar *m_pStatusbar;
    Centerbar *m_pCenterbar;
};

#endif // MAINWINDOWS_H
