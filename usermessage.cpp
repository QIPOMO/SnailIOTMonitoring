#include "usermessage.h"
#include "ui_usermessage.h"

UserMessage::UserMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMessage) {
    ui->setupUi(this);
    connect(ui->btnSeeOne,&QPushButton::clicked,this,[=](){
        emit display(0);
    });
    connect(ui->BtnChagePassword,&QPushButton::clicked,this,[=](){
        emit display(1);
    });
    connect(ui->btnDevice,&QPushButton::clicked,this,[=](){
        emit display(2);
        emit Device();
    });
    connect(ui->btnclose,&QPushButton::clicked,this,[=](){
        emit displayclose(0);
    });
}

UserMessage::~UserMessage()
{
    delete ui;
}
