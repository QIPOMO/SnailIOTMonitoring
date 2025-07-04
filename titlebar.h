#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
class Titlebar;
}

class Titlebar : public QWidget
{
    Q_OBJECT

public:
    explicit Titlebar(QWidget *parent = nullptr);
    ~Titlebar();

signals:
    void CloseCenter();
    void MinCenter();
    void MaxCenter();

private:
    Ui::Titlebar *ui;
};

#endif // TITLEBAR_H
