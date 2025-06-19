#include "admindevicemessage.h"
#include "ui_admindevicemessage.h"

adminDeviceMessage::adminDeviceMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDeviceMessage) {
    ui->setupUi(this);
    m_pDeviceMessage = new DeviceMessage;
    m_pDeviceLayout = new DeviceLayout;

    ui->DeviceMessage->addWidget(m_pDeviceMessage);
    ui->DeviceLayout->addWidget(m_pDeviceLayout);

    connect(m_pDeviceMessage,&DeviceMessage::display,m_pDeviceLayout,&DeviceLayout::display);


}

adminDeviceMessage::~adminDeviceMessage() {
    delete ui;

}
