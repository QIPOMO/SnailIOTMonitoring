#include "seeiddevice.h"
#include "ui_seeiddevice.h"

SeeIdDevice::SeeIdDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeeIdDevice)
{
    ui->setupUi(this);
}

SeeIdDevice::~SeeIdDevice()
{
    delete ui;
}
