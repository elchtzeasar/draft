TEMPLATE = app

QT += testlib
CONFIG += link_prl

INCLUDEPATH += ../gui/src ../remote_controller/include

LIBS += -L../libs -lgtest_main
LIBS += -L../libs -lremote_controller

SOURCES += remote_controller/RemoteControllerTest.cpp

TARGET = ../bin/unit_tests
