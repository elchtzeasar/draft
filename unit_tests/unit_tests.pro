TEMPLATE = app

QT += testlib network
CONFIG += link_prl

INCLUDEPATH += ../remote_controller/include
INCLUDEPATH += ../network/include ../network/src network/include

LIBS += -lgtest_main -lgmock -lgtest
LIBS += -L../libs -lremote_controller -lnetwork

HEADERS += network/include/ConnectionMock.h
HEADERS += network/include/ConnectionListenerMock.h
SOURCES += remote_controller/RemoteControllerTest.cpp
SOURCES += network/NetworkComponentTest.cpp

TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
