#include "admindataanalysis.h"
#include "ui_admindataanalysis.h"

adminDataAnalysis::adminDataAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminDataAnalysis)
{
    ui->setupUi(this);
}

adminDataAnalysis::~adminDataAnalysis()
{
    delete ui;
}
