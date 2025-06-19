#ifndef ADMINDATAANALYSIS_H
#define ADMINDATAANALYSIS_H

#include <QWidget>

namespace Ui {
class adminDataAnalysis;
}

class adminDataAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit adminDataAnalysis(QWidget *parent = nullptr);
    ~adminDataAnalysis();

private:
    Ui::adminDataAnalysis *ui;
};

#endif // ADMINDATAANALYSIS_H
