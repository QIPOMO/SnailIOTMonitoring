#ifndef USER_H
#define USER_H

#include <QWidget>
#include "usertitle.h"
#include "usermessage.h"
#include "userlayout.h"

namespace Ui {
class User;
}

class User : public QWidget
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();

signals:
    void LoginName(const QString &);
    void displayclose(int);

private:
    Ui::User *ui;
    UserTitle *m_pUserTitle;
    UserMessage *m_pUserMessage;
    UserLayout *m_pUserLayout;
};

#endif // USER_H
