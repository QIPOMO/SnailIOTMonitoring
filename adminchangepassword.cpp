#include "adminchangepassword.h"
#include "ui_adminchangepassword.h"
#include <QMessageBox>

adminChangePassword::adminChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminChangePassword),
    m_dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);

    ui->Username->setPlaceholderText("用户名");
    ui->Newpassword->setPlaceholderText("新密码");
    ui->Newrole->setPlaceholderText("权限[user or admin]");

    ui->Username->setAlignment(Qt::AlignCenter);
    ui->Newpassword->setAlignment(Qt::AlignCenter);
    ui->Newrole->setAlignment(Qt::AlignCenter);
    //ui->LoginPassword->setEchoMode(QLineEdit::Password);

    ui->Username->setAlignment(Qt::AlignCenter);
    ui->Newpassword->setAlignment(Qt::AlignCenter);

    connect(ui->btnChange,&QPushButton::clicked,this,&adminChangePassword::onChangePassword);

}


void adminChangePassword::onChangePassword() {
    DatabaseMessage user;

    QString name = ui->Username->text();
    QString newpassword = ui->Newpassword->text();
    QString newrole = ui->Newrole->text();
    if(!user.openDatabase()){
        QMessageBox::critical(this, "错误", "数据库打开失败", QMessageBox::Ok);
        user.closeDatabase();
        return;
    }

    user.updateUserPassword(user.getUserByName(name).user_id,newpassword);
    user.updateUserrole(name,newrole);
    ui->Username->clear();
    ui->Newpassword->clear();
    user.closeDatabase();
}


adminChangePassword::~adminChangePassword() {
    delete ui;
}
