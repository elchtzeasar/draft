TEMPLATE = app

QT += testlib
CONFIG += link_prl

INCLUDEPATH += ../gui/src ../remote_controller/include
INCLUDEPATH += remote_controller/include

LIBS += -lgtest_main
LIBS += -L../libs -lremote_controller

HEADERS += remote_controller/include/ConnectionMock.h
HEADERS += remote_controller/include/ConnectionListenerMock.h
SOURCES += remote_controller/RemoteControllerTest.cpp

TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
