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
    // 获取数据库单例
    DatabaseMessage* user = DatabaseMessage::instance();

    // 获取输入并去除两端空格
    QString name = ui->Newname->text().trimmed();
    QString password = ui->Newpassword->text();
    QString email = ui->NewEmail->text().trimmed();
    QString phone = ui->NewPhone->text().trimmed();
    QString nickname = ui->NewNickname->text().trimmed();

    // 验证必填字段
    if (name.isEmpty() || password.isEmpty() || email.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名、密码、邮箱和手机号不能为空");
        return;
    }

    // 邮箱格式简单验证
    if (!email.contains('@') || !email.contains('.')) {
        QMessageBox::warning(this, "输入错误", "邮箱格式不正确");
        return;
    }

    // 手机号简单验证（可根据实际需求调整）
    if (phone.length() < 6) {
        QMessageBox::warning(this, "输入错误", "手机号长度不足");
        return;
    }

    // 打开数据库
    if (!user->openDatabase()) {
        QMessageBox::critical(this, "数据库错误", "无法连接数据库");
        return;
    }

    try {
        // 检查用户名是否已存在（逻辑修正：user_id为0表示不存在）
        if (user->getUserByName(name).user_id != 0) {
            QMessageBox::warning(this, "注册失败", "用户名已存在");
            return;
        }

        // 检查邮箱是否已被使用
        if (user->getUserByEmail(email).user_id != 0) {
            QMessageBox::warning(this, "注册失败", "邮箱已被注册");
            return;
        }

        // 检查手机号是否已被使用
        if (user->getUserByPhone(phone).user_id != 0) {
            QMessageBox::warning(this, "注册失败", "手机号已被注册");
            return;
        }

        // 添加用户
        if (user->addUser(name, password, email, phone, nickname)) {
            QMessageBox::information(this, "成功", "用户注册成功");
            emit addsuccess(1);
            // 清空输入框
            ui->Newname->clear();
            ui->Newpassword->clear();
            ui->NewEmail->clear();
            ui->NewPhone->clear();
            ui->NewNickname->clear();
        } else {
            QMessageBox::warning(this, "错误", "用户注册失败");
            // emit addError(1);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "异常错误", QString("发生异常: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "未知错误", "发生未知异常");
    }
}

NewUser::~NewUser() {
    delete ui;

}


