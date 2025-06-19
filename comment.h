#ifndef COMMENT_H
#define COMMENT_H

#include <QApplication>
#include <QFile>
#include <QWidget>
#include <QTextStream>
#include <QDebug>

class Comment {
public:
    static void loadStyleSheep(const QString &filePath){
        QFile file(filePath);
        if(!file.open(QIODevice::ReadWrite)){
            return;
        }
        QTextStream out(&file);
        qApp->setStyleSheet(out.readAll());
        file.close();
    }
};

#endif // COMMENT_H
