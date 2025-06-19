#include "adddevice.h"
#include "ui_adddevice.h"


AddDevice::AddDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDevice){
    ui->setupUi(this);

    ui->Newname->setPlaceholderText("设备名");
    ui->Newtype->setPlaceholderText("设备类型");
    ui->Newlocation->setPlaceholderText("位置");
    ui->Newmanufacturer->setPlaceholderText("制造商(可空)");
    ui->Newmodel->setPlaceholderText("型号(可空)");
    ui->Newdata->setPlaceholderText("安装日期(可空)");

    ui->Newname->setAlignment(Qt::AlignCenter);
    ui->Newtype->setAlignment(Qt::AlignCenter);
    ui->Newlocation->setAlignment(Qt::AlignCenter);
    ui->Newmanufacturer->setAlignment(Qt::AlignCenter);
    ui->Newmodel->setAlignment(Qt::AlignCenter);
    ui->Newdata->setAlignment(Qt::AlignCenter);

    connect(ui->btnNewDevice,&QPushButton::clicked,this,&AddDevice::NewDevice);

}


// adddevice.cpp
void AddDevice::NewDevice() {
    DatabaseDevice* device = DatabaseDevice::instance(); // 使用单例
    if(!device->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开设备数据库");
        return;
    }

    QString Newname = ui->Newname->text().trimmed();
    QString Newtype = ui->Newtype->text().trimmed();
    QString Newlocation = ui->Newlocation->text().trimmed();

    if(Newname.isEmpty() || Newtype.isEmpty() || Newlocation.isEmpty()) {
        QMessageBox::warning(this, "警告", "设备名、类型和位置为必填项");
        return;
    }

    try {
        bool success = device->addDevice(
            Newname,
            Newtype,
            Newlocation,
            ui->Newmanufacturer->text().trimmed(),
            ui->Newmodel->text().trimmed(),
            QDateTime::currentDateTime()
        );

        if(success) {
            QMessageBox::information(this, "成功", "设备添加成功");
            ui->Newname->clear();
            ui->Newtype->clear();
            ui->Newlocation->clear();
            ui->Newmanufacturer->clear();
            ui->Newmodel->clear();
        } else {
            QMessageBox::warning(this, "错误", "设备添加失败");
        }
    } catch (...) {
        QMessageBox::critical(this, "错误", "添加设备时发生异常");
    }
}
AddDevice::~AddDevice() {
    delete ui;

}
