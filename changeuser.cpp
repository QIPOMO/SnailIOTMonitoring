#include "changeuser.h"
#include "ui_changeuser.h"

changeUser::changeUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeUser){
    ui->setupUi(this);

    ui->Oldpassword->setPlaceholderText("旧密码");
    ui->NewEmail->setPlaceholderText("新邮箱");
    ui->Newpassword->setPlaceholderText("新密码");
    ui->NewPhone->setPlaceholderText("新手机号");

    ui->Oldpassword->setAlignment(Qt::AlignCenter);
    ui->NewEmail->setAlignment(Qt::AlignCenter);
    ui->Newpassword->setAlignment(Qt::AlignCenter);
    ui->NewPhone->setAlignment(Qt::AlignCenter);
    //ui->LoginPassword->setEchoMode(QLineEdit::Password);

}

void changeUser::onGetUserall(const QString &name) {
    connect(ui->btnChange, &QPushButton::clicked, this, [=]() {
        // 获取数据库单例
        DatabaseMessage* user = DatabaseMessage::instance();

        // 获取输入并去除两端空格
        QString oldpassword = ui->Oldpassword->text();
        QString newEmail = ui->NewEmail->text().trimmed();
        QString newPhone = ui->NewPhone->text().trimmed();
        QString newPassword = ui->Newpassword->text();

        // 1. 检查数据库连接
        if (!user->openDatabase()) {
            QMessageBox::warning(this, "错误", "数据库打开失败");
            return;
        }

        try {
            // 2. 验证旧密码是否正确
            if (!user->authenticateUser(name, oldpassword)) {
                QMessageBox::warning(this, "错误", "旧密码不正确");
                return;
            }

            // 3. 获取当前用户信息
            DatabaseMessage::Users currentUser = user->getUserByName(name);
            if (currentUser.user_id == 0) {
                QMessageBox::warning(this, "错误", "用户不存在");
                return;
            }

            // 4. 确定要更新的值（如果输入框为空则保持原值）
            if (newEmail.isEmpty()) newEmail = currentUser.email;
            if (newPhone.isEmpty()) newPhone = currentUser.phone;

            // 5. 执行更新（只更新有变化的字段）
            bool success = true;
            QStringList failedUpdates;

            // 更新邮箱（如果变化了）
            if (newEmail != currentUser.email) {
                if (!user->updateUserEmail(name, newEmail)) {
                    success = false;
                    failedUpdates << "邮箱";
                }
            }

            // 更新电话（如果变化了）
            if (newPhone != currentUser.phone) {
                if (!user->updateUserphone(name, newPhone)) {
                    success = false;
                    failedUpdates << "电话";
                }
            }

            // 更新密码（只有在新密码不为空时才更新）
            if (!newPassword.isEmpty()) {
                if (!user->updateUserPassword(currentUser.user_id, newPassword)) {
                    success = false;
                    failedUpdates << "密码";
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
                QMessageBox::warning(this, "部分更新失败",
                    QString("以下信息更新失败:\n%1").arg(failedUpdates.join("\n")));
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "异常错误", QString("发生异常: %1").arg(e.what()));
        } catch (...) {
            QMessageBox::critical(this, "未知错误", "发生未知异常");
        }
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
