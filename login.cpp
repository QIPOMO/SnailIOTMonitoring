#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    m_dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);

    ui->LoginName->setPlaceholderText("用户名");
    ui->LoginPassword->setPlaceholderText("密码");

    ui->LoginName->setAlignment(Qt::AlignCenter);
    ui->LoginPassword->setAlignment(Qt::AlignCenter);
    //ui->LoginPassword->setEchoMode(QLineEdit::Password);

    connect(ui->btnLogin,&QPushButton::clicked,this,&Login::LoginSuccess);
    connect(ui->btnNewUser,&QPushButton::clicked,this,&Login::newUser);
    connect(ui->btnForgot,&QPushButton::clicked,this,&Login::RestPassword);
//    connect(this,&Login::getSerial,this,[=](const QByteArray &data){
//        const QByteArray &dataRef = data;
//    });
}



void Login::LoginSuccess() {

    DatabaseMessage user;
    QString name = ui->LoginName->text();
    QString password = ui->LoginPassword->text();
    if(!user.openDatabase()){
        return;
    }
    if (user.authenticateUser(name, password)) {
        if(user.getUserByName(name).role == "admin"){
            emit display(2);//管理员界面
//            emit getSerial(datas);

        }
        if(user.getUserByName(name).role == "user"){
            emit display(3);//普通用户界面
            emit disName(name);//把登陆时的名字传给user界面
        }
    }else{
        QMessageBox::information(this, "提示", "登录失败", QMessageBox::Ok);
    }
    user.closeDatabase();
    ui->LoginName->clear();
    ui->LoginPassword->clear();
}

void Login::RestPassword() {
     emit display(4);
}

void Login::newUser(){
    emit display(1);
}

Login::~Login() {
    delete ui;
}
