#include "admingetuserall.h"
#include "ui_admingetuserall.h"

adminGetUserAll::adminGetUserAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminGetUserAll){
    ui->setupUi(this);

}


void adminGetUserAll::onGetUserAll() {
    DatabaseMessage* user = DatabaseMessage::instance(); // 使用单例
    if(!user->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开用户数据库");
        return;
    }

    try {
        ui->textBrowser->clear();
        ui->textBrowser->append("============================================");

        QVector<DatabaseMessage::Users> users = user->getAllUsers();
        if (users.isEmpty()) {
            ui->textBrowser->append("没有用户数据！");
            return;
        }

        for (const DatabaseMessage::Users& u : users) {
            QString userInfo = QString(
                "用户ID: %1\n"
                "用户名: %2\n"
                "邮箱: %3\n"
                "电话: %4\n"
                "昵称: %5\n"
                "角色: %6\n"
                "------------------------------")
                .arg(u.user_id)
                .arg(u.username)
                .arg(u.email)
                .arg(u.phone)
                .arg(u.nickname.isEmpty() ? "无" : u.nickname)
                .arg(u.role);

            ui->textBrowser->append(userInfo);
        }
        ui->textBrowser->append("============ 数据结束 ============");
    } catch (...) {
        QMessageBox::critical(this, "错误", "获取用户数据时发生异常");
    }
}


adminGetUserAll::~adminGetUserAll() {
    delete ui;
}
