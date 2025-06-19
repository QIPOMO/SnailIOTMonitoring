#ifndef SEEIDDEVICE_H
#define SEEIDDEVICE_H

#include <QWidget>

namespace Ui {
class SeeIdDevice;
}

class SeeIdDevice : public QWidget
{
    Q_OBJECT

public:
    explicit SeeIdDevice(QWidget *parent = nullptr);
    ~SeeIdDevice();

private:
    Ui::SeeIdDevice *ui;
};

#endif // SEEIDDEVICE_H
