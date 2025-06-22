#include "adddevice.h"
#include "ui_adddevice.h"


AddDevice::AddDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDevice),
    dbDevice(new DatabaseDevice(this)){
    ui->setupUi(this);

    ui->Newname->setPlaceholderText("设备名");
    ui->Newtype->setPlaceholderText("设备类型");
    ui->Newlocation->setPlaceholderText("位置");
    ui->Newmanufacturer->setPlaceholderText("制造商(可空)");
    ui->Newmodel->setPlaceholderText("型号(可空)");

    ui->Newname->setAlignment(Qt::AlignCenter);
    ui->Newtype->setAlignment(Qt::AlignCenter);
    ui->Newlocation->setAlignment(Qt::AlignCenter);
    ui->Newmanufacturer->setAlignment(Qt::AlignCenter);
    ui->Newmodel->setAlignment(Qt::AlignCenter);

    connect(ui->btnNewDevice,&QPushButton::clicked,this,&AddDevice::NewDevice);

}


// adddevice.cpp
void AddDevice::NewDevice() {
    QString name = ui->Newname->text();
    QString type = ui->Newtype->text();
    QString location = ui->Newlocation->text();
    QString facturer = ui->Newmanufacturer->text();
    QString model = ui->Newmodel->text();
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    DatabaseDevice device;
    if(!device.openDatabase()){
        return;
    }
    if(!device.addDevice(name,type,location,facturer,model,dateTime)){
        return;
    }

    device.closeDatabase();
    ui->Newname->clear();
    ui->Newtype->clear();
    ui->Newlocation->clear();
    ui->Newmanufacturer->clear();
    ui->Newmodel->clear();
}
AddDevice::~AddDevice() {
    delete ui;

}
