#include "forgotpassword.h"
#include "ui_forgotpassword.h"

ForgotPassword::ForgotPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassword),
    m_dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);

    ui->EmailorPhone->setPlaceholderText("请输入邮箱号或者手机号");
    ui->Newpassword->setPlaceholderText("请输入新密码");
    ui->EmailorPhone->setAlignment(Qt::AlignCenter);
    ui->Newpassword->setAlignment(Qt::AlignCenter);

    connect(ui->btnLogin,&QPushButton::clicked,this,&ForgotPassword::onLogin);
    connect(ui->BtnFgt,&QPushButton::clicked,this,&ForgotPassword::onFgtPassword);

}

void ForgotPassword::onFgtPassword() {
    DatabaseMessage user;
    if(!user.openDatabase()){
        return;
    }
    if(user.updatePasswordByEmailOrPhone(ui->EmailorPhone->text(),ui->Newpassword->text())){
        qDebug()<<"密码修改成功";
    }else{
        qDebug()<<"密码修改失败";
    }
    ui->EmailorPhone->clear();
    ui->Newpassword->clear();
}

void ForgotPassword::onLogin() {
    emit display(0);
}

ForgotPassword::~ForgotPassword() {
    delete ui;

}
