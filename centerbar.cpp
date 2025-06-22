#include "centerbar.h"
#include "ui_centerbar.h"

Centerbar::Centerbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Centerbar) {
    ui->setupUi(this);

    m_pQStackedLayout = new QStackedLayout(this);

    m_pLogin = new Login;
    m_pNewUser = new NewUser;
    m_pAdmin = new Admin;
    m_pUser = new User;
    m_pForgotPassword = new ForgotPassword;

    m_pQStackedLayout->addWidget(m_pLogin);
    m_pQStackedLayout->addWidget(m_pNewUser);
    m_pQStackedLayout->addWidget(m_pAdmin);
    m_pQStackedLayout->addWidget(m_pUser);
    m_pQStackedLayout->addWidget(m_pForgotPassword);

    connect(m_pLogin,&Login::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pNewUser,&NewUser::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pForgotPassword,&ForgotPassword::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);

    connect(m_pUser,&User::displayclose,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(m_pAdmin,&Admin::displayclose,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);

    connect(m_pLogin,&Login::disName,m_pUser,&User::LoginName);
    connect(this,&Centerbar::getSerial,m_pAdmin,&Admin::getSerial);

}

Centerbar::~Centerbar()
{
    delete ui;
}
