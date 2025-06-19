#ifndef CHANGEUSER_H
#define CHANGEUSER_H

#include <QWidget>
#include "databasemessage.h"
#include <QMessageBox>

namespace Ui {
class changeUser;
}

class changeUser : public QWidget
{
    Q_OBJECT

public:
    explicit changeUser(QWidget *parent = nullptr);
    ~changeUser();
signals:
    void Loginname(const QString &);

public slots:
    void onGetUserall(const QString &);

private:
    Ui::changeUser *ui;

};

#endif // CHANGEUSER_H
