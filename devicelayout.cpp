#include "devicelayout.h"
#include "ui_devicelayout.h"

DeviceLayout::DeviceLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceLayout) {
    ui->setupUi(this);

    m_pQStackedLayout =new QStackedLayout(this);

    m_pdeviceManagerUser = new deviceManagerUser;
    m_pAddDevice = new AddDevice;
    m_padminDeleteDevice = new adminDeleteDevice;

    m_pQStackedLayout->addWidget(m_pdeviceManagerUser);
    m_pQStackedLayout->addWidget(m_pAddDevice);
    m_pQStackedLayout->addWidget(m_padminDeleteDevice);

    connect(this,&DeviceLayout::display,m_pQStackedLayout,&QStackedLayout::setCurrentIndex);
    connect(this,&DeviceLayout::Device,m_pdeviceManagerUser,&deviceManagerUser::onSeeDevice);
}

DeviceLayout::~DeviceLayout() {
    delete ui;
}
