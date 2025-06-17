#include "admingetuserall.h"
#include "ui_admingetuserall.h"

adminGetUserAll::adminGetUserAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminGetUserAll)
{
    ui->setupUi(this);
}

adminGetUserAll::~adminGetUserAll()
{
    delete ui;
}
