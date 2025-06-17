#ifndef DEVICEMANAGERUSER_H
#define DEVICEMANAGERUSER_H

#include <QWidget>

namespace Ui {
class deviceManagerUser;
}

class deviceManagerUser : public QWidget
{
    Q_OBJECT

public:
    explicit deviceManagerUser(QWidget *parent = nullptr);
    ~deviceManagerUser();

private:
    Ui::deviceManagerUser *ui;
};

#endif // DEVICEMANAGERUSER_H
