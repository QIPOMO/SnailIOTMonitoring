#include "adminlayout.h"
#include "ui_adminlayout.h"

AdminLayout::AdminLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLayout) {
    ui->setupUi(this);
    m_pQStackedLayout = new QStackedLayout(this);

    m_padminGetUserAll = new adminGetUserAll;
    m_padminChangePassword = new adminChangePassword;
    m_padminDeviceMessage = new adminDeviceMessage;
    m_padminDeviceError = new adminDeviceError;
    m_padminDataMessage = new adminDataMessage;
    m_padminDataAnalysis = new adminDataAnalysis;
    m_padminDeleteUser = new adminDeleteUser;
    m_padminLoginMessage = new adminLoginMessage;

    m_pQStackedLayout->addWidget(m_padminGetUserAll);
    m_pQStackedLayout->addWidget(m_padminChangePassword);
    m_pQStackedLayout->addWidget(m_padminDeviceMessage);
    m_pQStackedLayout->addWidget(m_padminDeviceError);
    m_pQStackedLayout->addWidget(m_padminDataMessage);
    m_pQStackedLayout->addWidget(m_padminDataAnalysis);
    m_pQStackedLayout->addWidget(m_padminDeleteUser);
    m_pQStackedLayout->addWidget(m_padminLoginMessage);

    connect(this,&AdminLayout::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);//跳转到想要的界面
    connect(this,&AdminLayout::display,m_padminGetUserAll,&adminGetUserAll::onGetUserAll);
    connect(this,&AdminLayout::getSerial,m_padminDeviceError,&adminDeviceError::getSerial);
    connect(this,&AdminLayout::getSerial,m_padminDataMessage,&adminDataMessage::getSerial);
}

AdminLayout::~AdminLayout()
{
    delete ui;
}
