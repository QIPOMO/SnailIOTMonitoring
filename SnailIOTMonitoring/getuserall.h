#ifndef GETUSERALL_H
#define GETUSERALL_H

#include <QWidget>
#include "databasemessage.h"

namespace Ui {
class getUserAll;
}

class getUserAll : public QWidget
{
    Q_OBJECT

public:
    explicit getUserAll(QWidget *parent = nullptr);
    ~getUserAll();

public slots:
    void onGetUserall(const QString &);

private:
    Ui::getUserAll *ui;
    DatabaseMessage *m_dbMessage;
};

#endif // GETUSERALL_H
