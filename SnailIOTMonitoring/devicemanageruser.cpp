#include "devicemanageruser.h"
#include "ui_devicemanageruser.h"

deviceManagerUser::deviceManagerUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deviceManagerUser)
{
    ui->setupUi(this);
}

deviceManagerUser::~deviceManagerUser()
{
    delete ui;
}
