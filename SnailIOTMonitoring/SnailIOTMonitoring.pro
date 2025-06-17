QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    adminchangepassword.cpp \
    admingetuserall.cpp \
    adminlayout.cpp \
    adminmessage.cpp \
    admintitle.cpp \
    basecenter.cpp \
    centerbar.cpp \
    changeuser.cpp \
    databasemessage.cpp \
    devicemanageruser.cpp \
    forgotpassword.cpp \
    getuserall.cpp \
    login.cpp \
    main.cpp \
    mainwindows.cpp \
    newuser.cpp \
    statusbar.cpp \
    titlebar.cpp \
    user.cpp \
    userlayout.cpp \
    usermessage.cpp \
    usertitle.cpp

HEADERS += \
    admin.h \
    adminchangepassword.h \
    admingetuserall.h \
    adminlayout.h \
    adminmessage.h \
    admintitle.h \
    basecenter.h \
    centerbar.h \
    changeuser.h \
    comment.h \
    databasemessage.h \
    devicemanageruser.h \
    forgotpassword.h \
    getuserall.h \
    login.h \
    mainwindows.h \
    newuser.h \
    statusbar.h \
    titlebar.h \
    user.h \
    userlayout.h \
    usermessage.h \
    usertitle.h

FORMS += \
    admin.ui \
    adminchangepassword.ui \
    admingetuserall.ui \
    adminlayout.ui \
    adminmessage.ui \
    admintitle.ui \
    centerbar.ui \
    changeuser.ui \
    devicemanageruser.ui \
    forgotpassword.ui \
    getuserall.ui \
    login.ui \
    mainwindows.ui \
    newuser.ui \
    statusbar.ui \
    titlebar.ui \
    user.ui \
    userlayout.ui \
    usermessage.ui \
    usertitle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    unilt/img.css

RESOURCES += \
    pros.qrc
