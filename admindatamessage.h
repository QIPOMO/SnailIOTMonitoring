#ifndef ADMINDATAMESSAGE_H
#define ADMINDATAMESSAGE_H

#include <QWidget>

namespace Ui {
class adminDataMessage;
}

class adminDataMessage : public QWidget
{
    Q_OBJECT

public:
    explicit adminDataMessage(QWidget *parent = nullptr);
    ~adminDataMessage();

private:
    Ui::adminDataMessage *ui;
};

#endif // ADMINDATAMESSAGE_H
