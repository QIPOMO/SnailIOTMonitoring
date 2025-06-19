#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login){
    ui->setupUi(this);

    ui->LoginName->setPlaceholderText("用户名");
    ui->LoginPassword->setPlaceholderText("密码");

    ui->LoginName->setAlignment(Qt::AlignCenter);
    ui->LoginPassword->setAlignment(Qt::AlignCenter);
    //ui->LoginPassword->setEchoMode(QLineEdit::Password);

    connect(ui->btnLogin,&QPushButton::clicked,this,&Login::LoginSuccess);
    connect(ui->btnNewUser,&QPushButton::clicked,this,&Login::newUser);
    connect(ui->btnForgot,&QPushButton::clicked,this,&Login::RestPassword);
}

void Login::LoginSuccess() {
    //获取单例实例
    DatabaseMessage* user = DatabaseMessage::instance();

    QString name = ui->LoginName->text();
    QString password = ui->LoginPassword->text();

    if(!user->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开数据库");
        return;
    }

    if (user->authenticateUser(name, password)) {
        DatabaseMessage::Users userInfo = user->getUserByName(name);
        if(userInfo.role == "admin"){
            emit display(2);//管理员界面
        }
        if(userInfo.role == "user"){
            emit display(3);//普通用户界面
            emit disName(name);//把登陆时的名字传给user界面
        }
    }

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
