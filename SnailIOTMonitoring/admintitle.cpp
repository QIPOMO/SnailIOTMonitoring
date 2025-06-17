#include "admintitle.h"
#include "ui_admintitle.h"

AdminTitle::AdminTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminTitle)
{
    ui->setupUi(this);
}

AdminTitle::~AdminTitle()
{
    delete ui;
}
