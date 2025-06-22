#ifndef ADMINCHANGEPASSWORD_H
#define ADMINCHANGEPASSWORD_H

#include <QWidget>
#include "databasemessage.h"

namespace Ui {
class adminChangePassword;
}

class adminChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit adminChangePassword(QWidget *parent = nullptr);
    ~adminChangePassword();

public slots:
    void onChangePassword();

private:
    Ui::adminChangePassword *ui;
    DatabaseMessage *m_dbMessage;

};

#endif // ADMINCHANGEPASSWORD_H
