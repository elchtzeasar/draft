TEMPLATE = app

QT += testlib network
CONFIG += link_prl

LIBS += -L/usr/local/include/glog -lglog
LIBS += -lgmock -lgtest
LIBS += -L../../libs

SOURCES += ../test_main.cpp

DIR_PREFIX = ..

# The following keeps the generated files at least somewhat separate 
OBJECTS_DIR = ../objs
