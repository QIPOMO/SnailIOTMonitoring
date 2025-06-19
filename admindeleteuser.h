#ifndef ADMINDELETEUSER_H
#define ADMINDELETEUSER_H

#include <QWidget>

namespace Ui {
class adminDeleteUser;
}

class adminDeleteUser : public QWidget
{
    Q_OBJECT

public:
    explicit adminDeleteUser(QWidget *parent = nullptr);
    ~adminDeleteUser();

private:
    Ui::adminDeleteUser *ui;
};

#endif // ADMINDELETEUSER_H
