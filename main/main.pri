TEMPLATE = app

INCLUDEPATH += ../gui/include ../remote_controller/include

OBJECTS_DIR = objs

HEADERS += ../main/DraftApplication.h
SOURCES += ../main/main.cpp

LIBS += -L../libs -lgui -lremote_controller
