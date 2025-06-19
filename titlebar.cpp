#include "titlebar.h"
#include "ui_titlebar.h"

Titlebar::Titlebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Titlebar) {
    ui->setupUi(this);

    connect(ui->btnClose,&QPushButton::clicked,this,&Titlebar::CloseCenter);
    connect(ui->btnMin,&QPushButton::clicked,this,&Titlebar::MinCenter);
    connect(ui->btnMax,&QPushButton::clicked,this,&Titlebar::MaxCenter);
}

Titlebar::~Titlebar()
{
    delete ui;
}
