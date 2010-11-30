TEMPLATE = app

QT += network

INCLUDEPATH += ../gui/include ../remote_controller/include
INCLUDEPATH += ../configuration/include ../network/include

OBJECTS_DIR = objs

HEADERS += ../main/DraftApplication.h
HEADERS += ../main/GuiDraftApplication.h
HEADERS += ../main/ConsoleDraftApplication.h

SOURCES += ../main/DraftApplication.cpp
SOURCES += ../main/GuiDraftApplication.cpp
SOURCES += ../main/ConsoleDraftApplication.cpp
SOURCES += ../main/main.cpp

LIBS += -L../libs -lgui -lremote_controller -lconfiguration -lnetwork
