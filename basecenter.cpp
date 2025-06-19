#include "basecenter.h"
#include <QDebug>

//#ifdef Q_OS_WIN
//#include <windows.h>
//#endif

BaseCenter::BaseCenter(QWidget *parent) : QWidget(parent) {

}

void BaseCenter::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){

//#ifdef Q_OS_WIN
//        ReleaseCapture();//释放当前鼠标捕获
//        //发送系统命令：SC_MOVE + HTCAPTION 组合模拟标题栏拖动
//        SendMessage(HWND(winId()),WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
//#else
        //鼠标全局坐标与窗口(左上角)的位置的差值
        m_pQPoint = event->globalPos() - frameGeometry().topLeft();
//#endif
    }
}

void BaseCenter::mouseReleaseEvent(QMouseEvent *event) {
    qDebug()<<event;
}

//#ifdef Q_OS_WIN
//#else
void BaseCenter::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() | Qt::LeftButton){
        move(event->globalPos() - m_pQPoint );
    }
}
//#endif
