#include "adminloginmessage.h"
#include "ui_adminloginmessage.h"

adminLoginMessage::adminLoginMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminLoginMessage)
{
    ui->setupUi(this);
}

adminLoginMessage::~adminLoginMessage()
{
    delete ui;
}
