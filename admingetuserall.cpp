#include "admingetuserall.h"
#include "ui_admingetuserall.h"

adminGetUserAll::adminGetUserAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminGetUserAll),
    dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);

}


void adminGetUserAll::onGetUserAll() {
    DatabaseMessage user;
    if(!user.openDatabase()){
        return;
    }
    ui->textBrowser->append("============================================");

    QVector<DatabaseMessage::Users> users = user.getAllUsers();
    if (users.isEmpty()) {
            ui->textBrowser->append("没有用户数据！");
            user.closeDatabase();
            return;
     }
    ui->textBrowser->clear();
    // 遍历并格式化每个用户信息
        for (const DatabaseMessage::Users& user : users) {
            QString userInfo = QString(
                "用户ID: %1\n"
                "用户名: %2\n"
                "邮箱: %3\n"
                "电话: %4\n"
                "昵称: %5\n"
                "角色: %6\n"
                "------------------------------")
                .arg(user.user_id)
                .arg(user.username)
                .arg(user.email)
                .arg(user.phone)
                .arg(user.nickname)
                .arg(user.role);

            ui->textBrowser->append(userInfo);
        }
        ui->textBrowser->append("============ 数据结束 ============");
        user.closeDatabase();
}



adminGetUserAll::~adminGetUserAll() {
    delete ui;
}
