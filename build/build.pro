TEMPLATE = app

INCLUDEPATH += ../gui/src
OBJECTS_DIR = objs
SOURCES += main.cpp

LIBS += -L../libs -lgui

TARGET = ../bin/draft
