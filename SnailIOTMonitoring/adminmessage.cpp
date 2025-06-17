#include "adminmessage.h"
#include "ui_adminmessage.h"

AdminMessage::AdminMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMessage) {
    ui->setupUi(this);

    connect(ui->btnSeeAll,&QPushButton::clicked,this,&AdminMessage::display);
    connect(ui->btnclose,&QPushButton::clicked,this,&AdminMessage::displayclose);
}

AdminMessage::~AdminMessage()
{
    delete ui;
}
