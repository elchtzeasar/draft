TEMPLATE = app

QT += network

INCLUDEPATH += ../gui/include ../remote_controller/include ../network/include

OBJECTS_DIR = objs

HEADERS += ../main/DraftApplication.h
SOURCES += ../main/main.cpp

LIBS += -L../libs -lgui -lremote_controller -lnetwork
