#ifndef ADMINLOGINMESSAGE_H
#define ADMINLOGINMESSAGE_H

#include <QWidget>

namespace Ui {
class adminLoginMessage;
}

class adminLoginMessage : public QWidget
{
    Q_OBJECT

public:
    explicit adminLoginMessage(QWidget *parent = nullptr);
    ~adminLoginMessage();

private:
    Ui::adminLoginMessage *ui;
};

#endif // ADMINLOGINMESSAGE_H
