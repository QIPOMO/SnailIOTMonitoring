#ifndef ADMINGETUSERALL_H
#define ADMINGETUSERALL_H

#include <QWidget>
#include "databasemessage.h"

namespace Ui {
class adminGetUserAll;
}

class adminGetUserAll : public QWidget
{
    Q_OBJECT

public:
    explicit adminGetUserAll(QWidget *parent = nullptr);
    ~adminGetUserAll();

public slots:
    void onGetUserAll();

private:
    Ui::adminGetUserAll *ui;
    DatabaseMessage *dbMessage;

};

#endif // ADMINGETUSERALL_H
