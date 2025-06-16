#include "login.h"
#include "ui_login.h"

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

    //Comment::loadStyleSheep("D:/qt/CenterWidget/uilte/bet.qss");

    connect(ui->btnLogin,&QPushButton::clicked,this,&Login::LoginSuccess);
    connect(ui->btnNewUser,&QPushButton::clicked,this,&Login::newUser);

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
        }
        if(user.getUserByName(name).role == "user"){
            emit display(3);//普通用户界面
        }
    }

    ui->LoginName->clear();
    ui->LoginPassword->clear();
}

void Login::newUser(){
    emit display(1);
}

Login::~Login() {
    delete ui;

}
