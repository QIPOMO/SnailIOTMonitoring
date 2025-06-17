#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include <QWidget>

namespace Ui {
class UserMessage;
}

class UserMessage : public QWidget {
    Q_OBJECT

public:
    explicit UserMessage(QWidget *parent = nullptr);
    ~UserMessage();

signals:
    void display(int);
    void displayclose(int);

private:
    Ui::UserMessage *ui;
};

#endif // USERMESSAGE_H
