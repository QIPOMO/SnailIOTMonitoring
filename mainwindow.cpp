#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_pQStackedLayout = new QStackedLayout(this);

    m_pLogin = new Login;
    m_pNewUser = new  NewUser;
    m_pAdmin = new Admin;
    m_pUser = new User;

    ui->centerLayout->addWidget(m_pLogin);
    ui->centerLayout->addWidget(m_pNewUser);
    ui->centerLayout->addWidget(m_pAdmin);
    ui->centerLayout->addWidget(m_pUser);

    m_pQStackedLayout->addWidget(m_pLogin);
    m_pQStackedLayout->addWidget(m_pNewUser);
    m_pQStackedLayout->addWidget(m_pAdmin);
    m_pQStackedLayout->addWidget(m_pUser);

    connect(m_pLogin,&Login::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    //connect(m_pNewUser,&NewUser::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);


}

MainWindow::~MainWindow() {
    delete ui;
    delete m_pLogin;
    delete m_pNewUser;
    delete m_pAdmin;
    delete m_pUser;
}

