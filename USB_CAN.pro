#-------------------------------------------------
#
# Project created by QtCreator 2018-06-16T10:20:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USB_CAN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    can_device.cpp \
    setup_page.cpp \
    update_page.cpp \
    src_file.cpp

HEADERS  += mainwindow.h \
    VCI_DLL.h \
    can_device.h \
    setup_page.h \
    can.h \
    update_page.h \
    src_file.h

LIBS += -LE:\Qt_projects\Qt_CAN_USB\USB_CAN\ -lVCI_CAN

FORMS    += mainwindow.ui \
    setup_page.ui \
    update_page.ui
