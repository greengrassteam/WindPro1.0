QT += core gui

# 开启QT图表
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pneumatic_balance_detection_system_for_wind_generator
TEMPLATE = app

# 定义警告
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
