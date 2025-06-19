#ifndef ADMINTITLE_H
#define ADMINTITLE_H

#include <QWidget>

namespace Ui {
class AdminTitle;
}

class AdminTitle : public QWidget
{
    Q_OBJECT

public:
    explicit AdminTitle(QWidget *parent = nullptr);
    ~AdminTitle();

private:
    Ui::AdminTitle *ui;
};

#endif // ADMINTITLE_H
