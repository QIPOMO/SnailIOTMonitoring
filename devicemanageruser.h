#ifndef DEVICEMANAGERUSER_H
#define DEVICEMANAGERUSER_H

#include <QWidget>
#include <QMessageBox>
#include "databasedevice.h"

namespace Ui {
class deviceManagerUser;
}

class deviceManagerUser : public QWidget
{
    Q_OBJECT

public:
    explicit deviceManagerUser(QWidget *parent = nullptr);
    ~deviceManagerUser();

public slots:
    void onSeeDevice();

private:
    Ui::deviceManagerUser *ui;
    DatabaseDevice *db_Device;
};

#endif // DEVICEMANAGERUSER_H
