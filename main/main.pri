TEMPLATE = app

QT += network

INCLUDEPATH += ../src
INCLUDEPATH += ../../common/include
INCLUDEPATH += ../../gui/include ../../remote_controller/include
INCLUDEPATH += ../../configuration/include ../../network/include
INCLUDEPATH += ../../state/include

OBJECTS_DIR = ../objs
MOC_DIR = ../mocs

HEADERS += ../src/DraftApplication.h
HEADERS += ../src/GuiDraftApplication.h
HEADERS += ../src/ConsoleDraftApplication.h

SOURCES += ../src/DraftApplication.cpp
SOURCES += ../src/GuiDraftApplication.cpp
SOURCES += ../src/ConsoleDraftApplication.cpp
SOURCES += ../main.cpp

LIBS += -L../../libs -lgui -lremote_controller -lconfiguration -lnetwork -lstate -lcommon
