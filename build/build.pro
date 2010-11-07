TEMPLATE = app

INCLUDEPATH += ../gui/include ../remote_control/include

OBJECTS_DIR = objs
SOURCES += main.cpp

LIBS += -L../libs -lgui -lremote_control

TARGET = ../bin/draft
