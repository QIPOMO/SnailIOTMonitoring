#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);  
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_pQStackedLayout = new QStackedLayout(this);

    m_pTitlebar = new Titlebar;
    m_pStatusbar = new Statusbar;

    m_pLogin = new Login;
    m_pNewUser = new  NewUser;
    m_pAdmin = new Admin;
    m_pUser = new User;
    m_pForgotPassword = new ForgotPassword;

    ui->TitlebarLayout->addWidget(m_pTitlebar);
    ui->centerbarLayout->addWidget(m_pLogin);
    ui->statusbar->addWidget(m_pStatusbar);

    ui->centerbarLayout->addWidget(m_pLogin);
    ui->centerbarLayout->addWidget(m_pNewUser);
    ui->centerbarLayout->addWidget(m_pAdmin);
    ui->centerbarLayout->addWidget(m_pUser);
    ui->centerbarLayout->addWidget(m_pForgotPassword);

    m_pQStackedLayout->addWidget(m_pLogin);
    m_pQStackedLayout->addWidget(m_pNewUser);
    m_pQStackedLayout->addWidget(m_pAdmin);
    m_pQStackedLayout->addWidget(m_pUser);
    m_pQStackedLayout->addWidget(m_pForgotPassword);


    connect(m_pTitlebar,&Titlebar::CloseCenter,this,&MainWindow::close);

    connect(m_pTitlebar,&Titlebar::MinCenter,this,[=](){
        this->showMinimized();
    });

    connect(m_pTitlebar,&Titlebar::MaxCenter,this,[=](){
        if (this->windowState() & Qt::WindowMaximized) {
            // 如果是最大化状态，则恢复为正常大小
            this->showNormal();
        } else {
            // 如果不是最大化状态，则最大化窗口
            this->showMaximized();
        }
    });

    connect(m_pLogin,&Login::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pNewUser,&NewUser::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pForgotPassword,&ForgotPassword::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);

}

MainWindow::~MainWindow() {
    delete ui;
}

