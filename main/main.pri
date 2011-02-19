TEMPLATE = app

QT += network

INCLUDEPATH += ../src
INCLUDEPATH += ../../common/include
INCLUDEPATH += ../../gui/include ../../remote_controller/include
INCLUDEPATH += ../../configuration/include ../../network/include
INCLUDEPATH += ../../state/include

OBJECTS_DIR = ../objs
MOC_DIR = ../mocs

SOURCES += ../main.cpp

DIR_PREFIX = ../..
! include( ../common/include/files.pri ) {
    error( Couldnt find the common/include/files.pri file! )
}
! include( ../configuration/include/files.pri ) {
    error( Couldnt find the configuration/include/files.pri file! )
}
! include( ../gui/include/files.pri ) {
    error( Couldnt find the gui/include/files.pri file! )
}
! include( ../remote_controller/include/files.pri ) {
    error( Couldnt find the remote_controller/include/files.pri file! )
}
! include( ../network/include/files.pri ) {
    error( Couldnt find the network/include/files.pri file! )
}
! include( ../state/include/files.pri ) {
    error( Couldnt find the state/include/files.pri file! )
}

LIBS += -L../../libs -lgui -lremote_controller -lconfiguration -lnetwork -lstate -lcommon
