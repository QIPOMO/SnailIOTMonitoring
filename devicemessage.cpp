#include "devicemessage.h"
#include "ui_devicemessage.h"

DeviceMessage::DeviceMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceMessage) {
    ui->setupUi(this);
    connect(ui->btnSeeDevice,&QPushButton::clicked,this,[=](){
        emit display(0);
    });
    connect(ui->btnAddDevice,&QPushButton::clicked,this,[=](){
        emit display(1);
    });
    connect(ui->btnGetDevice,&QPushButton::clicked,this,[=](){
        emit display(2);
    });
    connect(ui->btnDeleteDevice,&QPushButton::clicked,this,[=](){
        emit display(3);
    });
}

DeviceMessage::~DeviceMessage() {
    delete ui;
}
