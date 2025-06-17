#include "mainwindows.h"
#include "ui_mainwindows.h"

MainWindows::MainWindows(QWidget *parent) :
    BaseCenter(parent),
    ui(new Ui::MainWindows) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_pTitlebar = new Titlebar;
    m_pStatusbar = new Statusbar;
    m_pCenterbar = new Centerbar;

    ui->TitlebarLayout->addWidget(m_pTitlebar);
    ui->CenterbarLayout->addWidget(m_pCenterbar);
    ui->StatusbarLayout->addWidget(m_pStatusbar);

    connect(m_pTitlebar,&Titlebar::CloseCenter,this,&MainWindows::close);

    Comment::loadStyleSheep("D:/qt/SnailIOTMonitoring/unilt/img.css");

    connect(m_pTitlebar,&Titlebar::MinCenter,this,[=](){
        this->showMinimized();
    });

    connect(m_pTitlebar,&Titlebar::MaxCenter,this,[=](){
        if (this->windowState() & Qt::WindowMaximized) {
            // 如果是最大化状态，则恢复为正常大小
            this->showNormal();
        } else {
            // 如果不是最大化状态，则最大化窗口
            this->showMaximized();
        }
    });

}

MainWindows::~MainWindows()
{
    delete ui;
}
