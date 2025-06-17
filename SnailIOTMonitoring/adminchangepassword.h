#ifndef ADMINCHANGEPASSWORD_H
#define ADMINCHANGEPASSWORD_H

#include <QWidget>

namespace Ui {
class adminChangePassword;
}

class adminChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit adminChangePassword(QWidget *parent = nullptr);
    ~adminChangePassword();

private:
    Ui::adminChangePassword *ui;
};

#endif // ADMINCHANGEPASSWORD_H
