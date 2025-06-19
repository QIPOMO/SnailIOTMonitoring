#include "getuserall.h"
#include "ui_getuserall.h"

getUserAll::getUserAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getUserAll){
    ui->setupUi(this);
}



// getuserall.cpp
void getUserAll::onGetUserall(const QString &name) {
    DatabaseMessage* user = DatabaseMessage::instance(); // 使用单例
    if(!user->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开用户数据库");
        return;
    }

    try {
        ui->textEdit->clear();
        DatabaseMessage::Users userInfo = user->getUserByName(name);

        if(userInfo.user_id == 0) {
            QMessageBox::warning(this, "警告", "用户不存在");
            return;
        }

        ui->textEdit->append("昵称：" + (userInfo.nickname.isEmpty() ? "无" : userInfo.nickname));
        ui->textEdit->append("用户名：" + userInfo.username);
        ui->textEdit->append("邮箱：" + userInfo.email);
        ui->textEdit->append("手机号：" + userInfo.phone);
        ui->textEdit->append("权限：" + userInfo.role);
    } catch (...) {
        QMessageBox::critical(this, "错误", "获取用户信息时发生异常");
    }
}

getUserAll::~getUserAll() {
    delete ui;
}
