#include "adminchangepassword.h"
#include "ui_adminchangepassword.h"

adminChangePassword::adminChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminChangePassword)
{
    ui->setupUi(this);
}

adminChangePassword::~adminChangePassword()
{
    delete ui;
}
