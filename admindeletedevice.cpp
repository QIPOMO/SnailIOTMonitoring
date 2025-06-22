#include "admindeletedevice.h"
#include "ui_admindeletedevice.h"
#include <QMessageBox>

adminDeleteDevice::adminDeleteDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDeleteDevice),
    dbDevice(new DatabaseDevice (this)){
    ui->setupUi(this);
    connect(ui->btnDelete,&QPushButton::clicked,this,&adminDeleteDevice::onDeleteDevice);

}

void adminDeleteDevice::onDeleteDevice(){

    QString deciveName = ui->Devicename->text();
    QString deciveType = ui->DeviceType->text();
    //QMessageBox

    DatabaseDevice device;
    if(!device.openDatabase()){

        return;
    }
    if(device.getDeviceByName(deciveName).device_id == 0){
         QMessageBox::information(this, "提示", "设备不存在", QMessageBox::Ok);
        qDebug()<<"设备不存在";
         device.closeDatabase();
        return;
    }
    if(device.getDeviceByName(deciveName).type == deciveType){
        device.deleteDevice(device.getDeviceByName(deciveName).device_id);
        QMessageBox::question(this, "确认", "确定要删除吗?", QMessageBox::Yes | QMessageBox::No);
        qDebug()<<"设备已删除";
    }else{
        qDebug()<<"没有符合的设备";
    }
    device.closeDatabase();
    ui->Devicename->clear();
    ui->DeviceType->clear();
}

adminDeleteDevice::~adminDeleteDevice() {
    delete ui;

}


