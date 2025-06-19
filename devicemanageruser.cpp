#include "devicemanageruser.h"
#include "ui_devicemanageruser.h"
#include <QDateTime>

deviceManagerUser::deviceManagerUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deviceManagerUser){
    ui->setupUi(this);

}

void deviceManagerUser::onSeeDevice() {
    DatabaseDevice* device = DatabaseDevice::instance(); // 使用单例
    if(!device->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开设备数据库");
        return;
    }

    try {
        ui->DeviceMessage->clear();
        auto devices = device->getAllDevices();

        if (devices.isEmpty()) {
            ui->DeviceMessage->append("没有设备数据！");
            return;
        }

        ui->DeviceMessage->append("设备信息");
        for (const DatabaseDevice::Device& dev : devices) {
            QString deviceInfo = QString(
                        "设备ID: %1\n"
                        "设备名称: %2\n"
                        "设备类型: %3\n"
                        "位置: %4\n"
                        "制造商: %5\n"
                        "型号: %6\n"
                        "安装日期：%7\n"
                        "------------------------------")
                    .arg(dev.device_id)
                    .arg(dev.name)
                    .arg(dev.type)
                    .arg(dev.location)
                    .arg(dev.manufacturer.isEmpty() ? "无" : dev.manufacturer)
                    .arg(dev.model.isEmpty() ? "无" : dev.model)
                    .arg(dev.installation_date.toString("yyyy-MM-dd"));
            ui->DeviceMessage->append(deviceInfo);
        }
        ui->DeviceMessage->append("============ 数据结束 ============");
    } catch (...) {
        QMessageBox::critical(this, "错误", "获取设备数据时发生异常");
    }
}

deviceManagerUser::~deviceManagerUser() {
    delete ui;
}

