TEMPLATE = app

QT += testlib network
CONFIG += link_prl

LIBS += -L/usr/local/include/glog -lglog
LIBS += -lgmock -lgtest
LIBS += -L../libs -lremote_controllertest -lnetworktest -lconfigurationtest -lcommontest

SOURCES += test_main.cpp

DIR_PREFIX = ..

TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
OBJECTS_DIR = objs
