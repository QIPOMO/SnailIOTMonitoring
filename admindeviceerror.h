#ifndef ADMINDEVICEERROR_H
#define ADMINDEVICEERROR_H

#include <QWidget>

namespace Ui {
class adminDeviceError;
}

class adminDeviceError : public QWidget
{
    Q_OBJECT

public:
    explicit adminDeviceError(QWidget *parent = nullptr);
    ~adminDeviceError();

private:
    Ui::adminDeviceError *ui;
};

#endif // ADMINDEVICEERROR_H
