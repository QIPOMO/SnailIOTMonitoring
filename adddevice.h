#ifndef ADDDEVICE_H
#define ADDDEVICE_H

#include <QWidget>
#include "databasedevice.h"
#include <QDateTime>
#include <QMessageBox>
#include <QDateTime>

namespace Ui {
class AddDevice;
}

class AddDevice : public QWidget
{
    Q_OBJECT

public:
    explicit AddDevice(QWidget *parent = nullptr);
    ~AddDevice();

public slots:
    void NewDevice();

private:
    Ui::AddDevice *ui;
    DatabaseDevice *dbDevice;

};

#endif // ADDDEVICE_H
