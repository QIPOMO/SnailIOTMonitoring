#include "devicelayout.h"
#include "ui_devicelayout.h"

DeviceLayout::DeviceLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceLayout) {
    ui->setupUi(this);

    m_pQStackedLayout =new QStackedLayout(this);

    m_pdeviceManagerUser = new deviceManagerUser;
    m_pAddDevice = new AddDevice;
    m_pQStackedLayout->addWidget(m_pdeviceManagerUser);
    m_pQStackedLayout->addWidget(m_pAddDevice);

    connect(this,&DeviceLayout::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);

}

DeviceLayout::~DeviceLayout()
{
    delete ui;
}
