TEMPLATE = app

INCLUDEPATH += ../gui/src

OBJECTS_DIR = objs

SOURCES += main.cpp

LIBS += -L../gui -lgui

# Will build the final executable in the main project directory.

TARGET = ../bin/draft
