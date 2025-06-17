#include "userlayout.h"
#include "ui_userlayout.h"

UserLayout::UserLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserLayout) {
    ui->setupUi(this);

    m_pQStackedLayout = new QStackedLayout(this);
    m_pgetUserAll = new getUserAll;
    m_pchangeUser = new changeUser;
    m_pdeviceManagerUser = new deviceManagerUser;

    m_pQStackedLayout->addWidget(m_pgetUserAll);
    m_pQStackedLayout->addWidget(m_pchangeUser);
    m_pQStackedLayout->addWidget(m_pdeviceManagerUser);

    connect(this,&UserLayout::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(this,&UserLayout::Loginame,m_pgetUserAll,&getUserAll::onGetUserall);
    connect(this,&UserLayout::Loginame,m_pchangeUser,&changeUser::onGetUserall);
}

UserLayout::~UserLayout()
{
    delete ui;
}
