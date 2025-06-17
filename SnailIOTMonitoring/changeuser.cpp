#include "changeuser.h"
#include "ui_changeuser.h"

changeUser::changeUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeUser),
    m_dbMessage(new DatabaseMessage(this)){
    ui->setupUi(this);

}

void changeUser::onGetUserall(const QString &name) {
    connect(ui->btnChange, &QPushButton::clicked, this, [=]() {
        DatabaseMessage user;
        QString oldpassword = ui->Oldpassword->text();

        // 1. 先检查数据库连接
        if (!user.openDatabase()) {
            QMessageBox::warning(this, "错误", "数据库打开失败");
            return;
        }

        // 2. 验证旧密码是否正确
        if (!user.authenticateUser(name, oldpassword)) {
            QMessageBox::warning(this, "错误", "旧密码不正确");
            user.closeDatabase();
            return;
        }

        // 3. 获取当前用户信息

        if (user.getUserByName(name).user_id == 0) {
            QMessageBox::warning(this, "错误", "用户不存在");
            user.closeDatabase();
            return;
        }

        // 4. 确定要更新的值（如果输入框为空则保持原值）
        QString newEmail = ui->NewEmail->text().isEmpty() ? user.getUserByName(name).email : ui->NewEmail->text();
        QString newPhone = ui->NewPhone->text().isEmpty() ? user.getUserByName(name).phone : ui->NewPhone->text();

        // 5. 执行更新（只更新有变化的字段）
        bool success = true;

        // 更新邮箱（如果变化了）
        if (newEmail != user.getUserByName(name).email) {
            if (!user.updateUserEmail(name, newEmail)) {
                success = false;
            }
        }

        // 更新电话（如果变化了）
        if (newPhone != user.getUserByName(name).phone) {
            if (!user.updateUserphone(name, newPhone)) {
                success = false;
            }
        }

        // 更新密码（只有在新密码不为空时才更新）
        if (!ui->Newpassword->text().isEmpty()) {
            if (!user.updateUserPassword(user.getUserByName(name).user_id, ui->Newpassword->text())) {
                success = false;
            }
        }

        // 6. 处理结果
        if (success) {
            QMessageBox::information(this, "成功", "修改成功");
            // 清空输入框
            ui->NewEmail->clear();
            ui->NewPhone->clear();
            ui->Newpassword->clear();
            ui->Oldpassword->clear();
        } else {
            QMessageBox::warning(this, "错误", "部分更新失败");
        }

        user.closeDatabase();
    });
}



//void changeUser::onGetUserall(const QString &name) {
//    connect(ui->btnChange,&QPushButton::clicked,this,[=](){
//        DatabaseMessage user;
//        QString oldpassword = ui->Oldpassword->text();
//        qDebug()<<"Oldpassword:"<<oldpassword;

//        QString Newpassword = ui->Newpassword->text();
//        QString Email = ui->NewEmail->text();
//        QString phone = ui->NewPhone->text();
//        if(!user.openDatabase()){
//            qDebug()<<"Error：数据库打开失败";
//            return;
//        }
//        if(user.authenticateUser(name,oldpassword)){
//                user.updateUserEmail(name,Email);
//                user.updateUserphone(name,phone);
//                user.updateUserPassword(user.getUserByName(name).user_id,Newpassword);
//                if(ui->NewEmail->text() == nullptr){
//                    user.updateUserEmail(name,user.getUserByName(name).email);
//                }
//                if(ui->NewPhone->text() == nullptr){
//                    user.updateUserphone(name,user.getUserByName(name).phone);
//                }
//                if(ui->Newpassword->text() == nullptr){
//                    user.updateUserPassword(user.getUserByName(name).user_id,user.getUserByName(name).password);
//                }
//                qDebug()<<"修改成功";
//            user.closeDatabase();
//            ui->NewEmail->clear();
//            ui->NewPhone->clear();
//            ui->Newpassword->clear();
//            ui->Oldpassword->clear();
//        }else{
//            qDebug()<<"错误";
//            qDebug()<<"试着了吗";
//            user.closeDatabase();
//        }

//    });

//}


changeUser::~changeUser() {
    delete ui;

}
