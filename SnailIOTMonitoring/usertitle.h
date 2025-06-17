#ifndef USERTITLE_H
#define USERTITLE_H

#include <QWidget>

namespace Ui {
class UserTitle;
}

class UserTitle : public QWidget
{
    Q_OBJECT

public:
    explicit UserTitle(QWidget *parent = nullptr);
    ~UserTitle();

private:
    Ui::UserTitle *ui;
};

#endif // USERTITLE_H
