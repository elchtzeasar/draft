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

DIR_PREFIX = ..
! include( ../common/include/files.pri ) {
    error( Couldnt find the common public_files.pri file! )
}
! include( ../configuration/include/files.pri ) {
    error( Couldnt find the configuration public_files.pri file! )
}
! include( ../gui/public_files.pri ) {
    error( Couldnt find the gui public_files.pri file! )
}
! include( ../remote_controller/public_files.pri ) {
    error( Couldnt find the remote_controller public_files.pri file! )
}
! include( ../network/public_files.pri ) {
    error( Couldnt find the network public_files.pri file! )
}
! include( ../state/public_files.pri ) {
    error( Couldnt find the state public_files.pri file! )
}

LIBS += -L../../libs -lgui -lremote_controller -lconfiguration -lnetwork -lstate -lcommon
