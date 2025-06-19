#include "forgotpassword.h"
#include "ui_forgotpassword.h"

ForgotPassword::ForgotPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassword){
    ui->setupUi(this);

    ui->EmailorPhone->setPlaceholderText("请输入邮箱号或者手机号");
    ui->Newpassword->setPlaceholderText("请输入新密码");
    ui->EmailorPhone->setAlignment(Qt::AlignCenter);
    ui->Newpassword->setAlignment(Qt::AlignCenter);

    connect(ui->btnLogin,&QPushButton::clicked,this,&ForgotPassword::onLogin);
    connect(ui->BtnFgt,&QPushButton::clicked,this,&ForgotPassword::onFgtPassword);

}

// forgotpassword.cpp
void ForgotPassword::onFgtPassword() {
    DatabaseMessage* user = DatabaseMessage::instance(); // 使用单例
    if(!user->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开用户数据库");
        return;
    }

    QString emailOrPhone = ui->EmailorPhone->text().trimmed();
    QString newPassword = ui->Newpassword->text();

    if(emailOrPhone.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "警告", "邮箱/手机号和新密码不能为空");
        return;
    }

    try {
        if(user->updatePasswordByEmailOrPhone(emailOrPhone, newPassword)) {
            QMessageBox::information(this, "成功", "密码修改成功");
            ui->EmailorPhone->clear();
            ui->Newpassword->clear();
        } else {
            QMessageBox::warning(this, "错误", "密码修改失败，请检查输入信息");
        }
    } catch (...) {
        QMessageBox::critical(this, "错误", "修改密码时发生异常");
    }
}
void ForgotPassword::onLogin() {
    emit display(0);
}

ForgotPassword::~ForgotPassword() {
    delete ui;

}
