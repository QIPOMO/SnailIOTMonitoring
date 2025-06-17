#ifndef ADMINGETUSERALL_H
#define ADMINGETUSERALL_H

#include <QWidget>

namespace Ui {
class adminGetUserAll;
}

class adminGetUserAll : public QWidget
{
    Q_OBJECT

public:
    explicit adminGetUserAll(QWidget *parent = nullptr);
    ~adminGetUserAll();

private:
    Ui::adminGetUserAll *ui;
};

#endif // ADMINGETUSERALL_H
