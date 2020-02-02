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
    Clients/clienteditdialog.cpp \
    Clients/clientsdialog.cpp \
    Clients/modelobjects.cpp \
    Clients/modelusers.cpp \
    Clients/objecteditdialog.cpp \
    Clients/usereditdialog.cpp \
    DataBase/database.cpp \
    DataBase/datbasesettingsdialog.cpp \
    LoggingCategories/loggingcategories.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Clients/clienteditdialog.h \
    Clients/clientsdialog.h \
    Clients/modelobjects.h \
    Clients/modelusers.h \
    Clients/objecteditdialog.h \
    Clients/usereditdialog.h \
    DataBase/database.h \
    DataBase/datbasesettingsdialog.h \
    LoggingCategories/loggingcategories.h \
    SearchConfigFile.h \
    mainwindow.h

FORMS += \
    Clients/clienteditdialog.ui \
    Clients/clientsdialog.ui \
    Clients/objecteditdialog.ui \
    Clients/usereditdialog.ui \
    DataBase/datbasesettingsdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    MPosWebAdmin_uk_UA.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../etc/MPosWebServer.ini

RESOURCES += \
    resource.qrc
