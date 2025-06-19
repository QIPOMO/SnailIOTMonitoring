#include "admindeleteuser.h"
#include "ui_admindeleteuser.h"

adminDeleteUser::adminDeleteUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDeleteUser)
{
    ui->setupUi(this);
}

adminDeleteUser::~adminDeleteUser()
{
    delete ui;
}
