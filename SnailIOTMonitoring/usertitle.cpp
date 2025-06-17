#include "usertitle.h"
#include "ui_usertitle.h"

UserTitle::UserTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTitle)
{
    ui->setupUi(this);
}

UserTitle::~UserTitle()
{
    delete ui;
}
