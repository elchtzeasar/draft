TEMPLATE = app

INCLUDEPATH += ../gui/src ../remote_controller/include

LIBS += -L../libs -lgtest_main
LIBS += -L../libs -lgui -lremote_controller

#SOURCES += gui/test_gui.cpp

TARGET = ../bin/unit_tests
