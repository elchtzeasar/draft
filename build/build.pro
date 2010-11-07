TEMPLATE = app

INCLUDEPATH += ../gui/include
OBJECTS_DIR = objs
SOURCES += main.cpp

LIBS += -L../libs -lgui

TARGET = ../bin/draft
