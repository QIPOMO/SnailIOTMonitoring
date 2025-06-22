#include "getuserall.h"
#include "ui_getuserall.h"

getUserAll::getUserAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getUserAll),
    m_dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);
}



void getUserAll::onGetUserall(const QString &name) {
    DatabaseMessage user;
    if(!user.openDatabase()){
        return;
    }
    ui->textEdit->clear();
    ui->textEdit->append("===============个人信息==============");
    ui->textEdit->append("昵称：" +user.getUserByName(name).nickname);
    ui->textEdit->append("用户名：" +user.getUserByName(name).username);
    ui->textEdit->append("邮箱：" +user.getUserByName(name).email);
    ui->textEdit->append("手机号：" +user.getUserByName(name).phone);
    ui->textEdit->append("权限：" +user.getUserByName(name).role);
    ui->textEdit->append("======================================");
    user.closeDatabase();
}

getUserAll::~getUserAll() {
    delete ui;
}
