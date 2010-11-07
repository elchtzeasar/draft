TEMPLATE = app

INCLUDEPATH += ../gui/include ../remote_controller/include

OBJECTS_DIR = objs
SOURCES += main.cpp

LIBS += -L../libs -lgui -lremote_controller

TARGET = ../bin/draft
