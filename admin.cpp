#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin) {
    ui->setupUi(this);

    m_pAdminTitle = new AdminTitle;
    m_pAdminMessage = new AdminMessage;
    m_pAdminLayout = new AdminLayout;

    ui->AdminTitle->addWidget(m_pAdminTitle);
    ui->AdminMessage->addWidget(m_pAdminMessage);
    ui->AdminLayout->addWidget(m_pAdminLayout);


    connect(m_pAdminMessage,&AdminMessage::displayclose,this,&Admin::displayclose);
    connect(m_pAdminMessage,&AdminMessage::display,m_pAdminLayout,&AdminLayout::display);
    connect(this,&Admin::getSerial,m_pAdminLayout,&AdminLayout::getSerial);

}

Admin::~Admin() {
    delete ui;
}
