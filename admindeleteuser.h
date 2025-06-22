#ifndef ADMINDELETEUSER_H
#define ADMINDELETEUSER_H

#include <QWidget>
#include "databasemessage.h"

namespace Ui {
class adminDeleteUser;
}

class adminDeleteUser : public QWidget {
    Q_OBJECT

public:
    explicit adminDeleteUser(QWidget *parent = nullptr);
    ~adminDeleteUser();

public slots:
    void onDelete();

private:
    Ui::adminDeleteUser *ui;
    DatabaseMessage *dbMessage;
};

#endif // ADMINDELETEUSER_H
