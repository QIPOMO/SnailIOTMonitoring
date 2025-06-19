#include "statusbar.h"
#include "ui_statusbar.h"

Statusbar::Statusbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statusbar)
{
    ui->setupUi(this);
}

Statusbar::~Statusbar()
{
    delete ui;
}
