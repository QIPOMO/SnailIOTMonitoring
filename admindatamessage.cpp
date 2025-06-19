#include "admindatamessage.h"
#include "ui_admindatamessage.h"

adminDataMessage::adminDataMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDataMessage)
{
    ui->setupUi(this);
}

adminDataMessage::~adminDataMessage()
{
    delete ui;
}
