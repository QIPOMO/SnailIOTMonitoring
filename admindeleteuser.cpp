#include "admindeleteuser.h"
#include "ui_admindeleteuser.h"
#include <QMessageBox>

adminDeleteUser::adminDeleteUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDeleteUser),
    dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);
    connect(ui->btnDelete,&QPushButton::clicked,this,&adminDeleteUser::onDelete);
}

void adminDeleteUser::onDelete(){
    QString name = ui->userName->text();
    DatabaseMessage user;
    if(!user.openDatabase()){
        return;
    }
    if(!user.userExists(name)){
        user.closeDatabase();
        return;
    }
    if(!user.deleteUserByName(name)){
        return;
    }else{
        QMessageBox::information(this, "提示", "操作成功完成", QMessageBox::Ok);
    }
    user.closeDatabase();
    ui->userName->clear();
}

adminDeleteUser::~adminDeleteUser(){
    delete ui;
}

