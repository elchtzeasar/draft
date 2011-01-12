TEMPLATE = app

QT += testlib network
CONFIG += link_prl

INCLUDEPATH += ../common/include
INCLUDEPATH += ../remote_controller/include
INCLUDEPATH += ../network/include ../network/src network/include
INCLUDEPATH += ../configuration/include ../configuration/src configuration/include

LIBS += -lgmock -lgtest
LIBS += -L../libs -lremote_controllertest -lnetworktest -lconfigurationtest -lcommontest

SOURCES += test_main.cpp

DIR_PREFIX = ..


TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
