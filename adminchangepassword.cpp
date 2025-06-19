#include "adminchangepassword.h"
#include "ui_adminchangepassword.h"

adminChangePassword::adminChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminChangePassword){
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
    // 获取单例实例
    DatabaseMessage* user = DatabaseMessage::instance();

    // 获取输入并去除两端空格
    QString name = ui->Username->text().trimmed();
    QString newpassword = ui->Newpassword->text();
    QString newrole = ui->Newrole->text().trimmed().toLower();

    // 验证输入
    if(name.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名不能为空");
        return;
    }

    if(newrole != "user" && newrole != "admin") {
        QMessageBox::warning(this, "警告", "角色必须是 user 或 admin");
        return;
    }

    // 打开数据库
    if(!user->openDatabase()){
        QMessageBox::warning(this, "错误", "无法打开数据库");
        return;
    }

    try {
        // 检查用户是否存在
        DatabaseMessage::Users existingUser = user->getUserByName(name);
        if(existingUser.user_id == 0) {
            QMessageBox::warning(this, "错误", "用户不存在");
            return;
        }

        // 更新密码和角色
        bool passwordUpdated = true;
        if(!newpassword.isEmpty()) {
            passwordUpdated = user->updateUserPassword(existingUser.user_id, newpassword);
        }

        bool roleUpdated = user->updateUserrole(name, newrole);

        if(passwordUpdated && roleUpdated) {
            QMessageBox::information(this, "成功", "用户信息更新成功");
            ui->Username->clear();
            ui->Newpassword->clear();
            ui->Newrole->clear();
        } else {
            QString errorMsg;
            if(!passwordUpdated) errorMsg += "密码更新失败\n";
            if(!roleUpdated) errorMsg += "角色更新失败";
            QMessageBox::warning(this, "错误", errorMsg);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "异常错误", QString("发生异常: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "未知错误", "发生未知异常");
    }
}

adminChangePassword::~adminChangePassword() {
    delete ui;
}
