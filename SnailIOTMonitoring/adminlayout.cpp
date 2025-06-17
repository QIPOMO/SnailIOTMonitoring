#include "adminlayout.h"
#include "ui_adminlayout.h"

AdminLayout::AdminLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLayout) {
    ui->setupUi(this);
    m_pQStackedLayout = new QStackedLayout(this);

    m_padminGetUserAll = new adminGetUserAll;
    m_padminChangePassword = new adminChangePassword;

    m_pQStackedLayout->addWidget(m_padminGetUserAll);
    m_pQStackedLayout->addWidget(m_padminChangePassword);



}

AdminLayout::~AdminLayout()
{
    delete ui;
}
