#include "admindeviceerror.h"
#include "ui_admindeviceerror.h"

adminDeviceError::adminDeviceError(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDeviceError)
{
    ui->setupUi(this);
}

adminDeviceError::~adminDeviceError()
{
    delete ui;
}
