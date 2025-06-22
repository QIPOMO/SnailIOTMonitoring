QT       += core gui sql serialport charts

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
    adddevice.cpp \
    admin.cpp \
    adminchangepassword.cpp \
    admindataanalysis.cpp \
    admindatamessage.cpp \
    admindeletedevice.cpp \
    admindeleteuser.cpp \
    admindeviceerror.cpp \
    admindevicemessage.cpp \
    admingetuserall.cpp \
    adminlayout.cpp \
    adminloginmessage.cpp \
    adminmessage.cpp \
    admintitle.cpp \
    basecenter.cpp \
    centerbar.cpp \
    changeuser.cpp \
    databasedevice.cpp \
    databasemessage.cpp \
    databasestm.cpp \
    devicelayout.cpp \
    devicemanageruser.cpp \
    devicemessage.cpp \
    forgotpassword.cpp \
    getuserall.cpp \
    login.cpp \
    main.cpp \
    mainwindows.cpp \
    newuser.cpp \
    serial.cpp \
    statusbar.cpp \
    titlebar.cpp \
    user.cpp \
    userlayout.cpp \
    usermessage.cpp \
    usertitle.cpp

HEADERS += \
    adddevice.h \
    admin.h \
    adminchangepassword.h \
    admindataanalysis.h \
    admindatamessage.h \
    admindeletedevice.h \
    admindeleteuser.h \
    admindeviceerror.h \
    admindevicemessage.h \
    admingetuserall.h \
    adminlayout.h \
    adminloginmessage.h \
    adminmessage.h \
    admintitle.h \
    basecenter.h \
    centerbar.h \
    changeuser.h \
    comment.h \
    databasedevice.h \
    databasemessage.h \
    databasestm.h \
    devicelayout.h \
    devicemanageruser.h \
    devicemessage.h \
    forgotpassword.h \
    getuserall.h \
    login.h \
    mainwindows.h \
    newuser.h \
    serial.h \
    statusbar.h \
    titlebar.h \
    user.h \
    userlayout.h \
    usermessage.h \
    usertitle.h

FORMS += \
    adddevice.ui \
    admin.ui \
    adminchangepassword.ui \
    admindataanalysis.ui \
    admindatamessage.ui \
    admindeletedevice.ui \
    admindeleteuser.ui \
    admindeviceerror.ui \
    admindevicemessage.ui \
    admingetuserall.ui \
    adminlayout.ui \
    adminloginmessage.ui \
    adminmessage.ui \
    admintitle.ui \
    centerbar.ui \
    changeuser.ui \
    devicelayout.ui \
    devicemanageruser.ui \
    devicemessage.ui \
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
