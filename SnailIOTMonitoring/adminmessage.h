#ifndef ADMINMESSAGE_H
#define ADMINMESSAGE_H

#include <QWidget>

namespace Ui {
class AdminMessage;
}

class AdminMessage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMessage(QWidget *parent = nullptr);
    ~AdminMessage();

signals:
    void display(int);
    void displayclose(int);

private:
    Ui::AdminMessage *ui;
};

#endif // ADMINMESSAGE_H
