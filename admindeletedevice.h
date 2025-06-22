#ifndef ADMINDELETEDEVICE_H
#define ADMINDELETEDEVICE_H

#include <QWidget>
#include "databasedevice.h"

namespace Ui {
class adminDeleteDevice;
}

class adminDeleteDevice : public QWidget
{
    Q_OBJECT

public:
    explicit adminDeleteDevice(QWidget *parent = nullptr);
    ~adminDeleteDevice();

public slots:
    void onDeleteDevice();

private:
    Ui::adminDeleteDevice *ui;
    DatabaseDevice *dbDevice;
};

#endif // ADMINDELETEDEVICE_H
