#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User) {
    ui->setupUi(this);

    m_pUserTitle = new UserTitle;
    m_pUserMessage = new UserMessage;
    m_pUserLayout = new UserLayout;

    ui->UserTitle->addWidget(m_pUserTitle);
    ui->UserMessage->addWidget(m_pUserMessage);
    ui->UserLayout->addWidget(m_pUserLayout);

    connect(m_pUserMessage,&UserMessage::display,m_pUserLayout,&UserLayout::display);
    connect(m_pUserMessage,&UserMessage::Device,m_pUserLayout,&UserLayout::Device);
    connect(m_pUserMessage,&UserMessage::displayclose,this,&User::displayclose);

    connect(this,&User::LoginName,m_pUserLayout,&UserLayout::Loginame);

}

User::~User() {
    delete ui;

}
