#ifndef BASECENTER_H
#define BASECENTER_H

#include <QWidget>
#include <QMouseEvent>


class BaseCenter : public QWidget {
    Q_OBJECT
public:
    explicit BaseCenter(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint m_pQPoint;//坐标位置

};

#endif // BASECENTER_H
