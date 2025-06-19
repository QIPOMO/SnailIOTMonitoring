#include "adminmessage.h"
#include "ui_adminmessage.h"

AdminMessage::AdminMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMessage) {
    ui->setupUi(this);

    connect(ui->btnSeeAll,&QPushButton::clicked,this,[=](){
        emit display(0);
    });
    connect(ui->btnChagePassword,&QPushButton::clicked,this,[=](){
        emit display(1);
    });
    connect(ui->btnDeviceMassage,&QPushButton::clicked,this,[=](){
        emit display(2);
    });
    connect(ui->btnChagePassword,&QPushButton::clicked,this,[=](){
        emit display(3);
    });
    connect(ui->btnError,&QPushButton::clicked,this,[=](){
        emit display(4);
    });
    connect(ui->btnDataMessage,&QPushButton::clicked,this,[=](){
        emit display(5);
    });
    connect(ui->btnDataAnalysis,&QPushButton::clicked,this,[=](){
        emit display(6);
    });
    connect(ui->btnDeleteUser,&QPushButton::clicked,this,[=](){
        emit display(7);
    });
    connect(ui->btnLoginMessage,&QPushButton::clicked,this,[=](){
        emit display(8);
    });

    connect(ui->btnclose,&QPushButton::clicked,this,&AdminMessage::displayclose);
}

AdminMessage::~AdminMessage()
{
    delete ui;
}
