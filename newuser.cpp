#include "newuser.h"
#include "ui_newuser.h"

NewUser::NewUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewUser) {
    ui->setupUi(this);

    ui->Newname->setPlaceholderText("用户名");
    ui->Newpassword->setPlaceholderText("密码");
    ui->NewEmail->setPlaceholderText("邮件");
    ui->NewPhone->setPlaceholderText("手机号");
    ui->NewNickname->setPlaceholderText("昵称(可以不输入)");

    ui->Newname->setAlignment(Qt::AlignCenter);
    ui->Newpassword->setAlignment(Qt::AlignCenter);
    ui->NewEmail->setAlignment(Qt::AlignCenter);
    ui->NewPhone->setAlignment(Qt::AlignCenter);
    ui->NewNickname->setAlignment(Qt::AlignCenter);

    ui->Newpassword->setEchoMode(QLineEdit::Password);

    connect(ui->btnNewUser,&QPushButton::clicked,this,&NewUser::addNewuser);
    connect(ui->btnlogin,&QPushButton::clicked,this,[=](){
        emit display(0);
    });

}

void NewUser::addNewuser() {
    DatabaseMessage  user;
    QString name = ui->Newname->text();
    QString password = ui->Newpassword->text();
    QString email = ui->NewEmail->text();
    QString phone = ui->NewPhone->text();
    QString nickname= ui->NewNickname->text();

    if(!user.openDatabase()){
        return;
    }
    // 检查用户名是否有效
    if (name.isEmpty() || password.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        qDebug() << "用户名\\密码\\邮箱\\手机号不能为空";
        QMessageBox::warning(this, "警告", "用户名\\密码\\邮箱\\手机号不能为空", QMessageBox::Ok);
        return;
    }

     //检查用户名是否已存在
    if (user.getUserByName(name).user_id == 0) {
        qDebug() << "用户名已存在";
        QMessageBox::information(this, "提示", "用户名已存在", QMessageBox::Ok);
        return;
    }

    if(user.addUser(name,password,email,phone,nickname)){
        emit addsuccess(1);
    }
    else{
       QMessageBox::critical(this, "错误", "注册失败", QMessageBox::Ok);
        return;
    }
    user.closeDatabase();
    ui->Newname->clear();
    ui->Newpassword->clear();
    ui->NewEmail->clear();
    ui->NewPhone->clear();
    ui->NewNickname->clear();
}

NewUser::~NewUser() {
    delete ui;

}


