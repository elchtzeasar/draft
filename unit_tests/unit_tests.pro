TEMPLATE = app

QT += testlib network
CONFIG += link_prl

INCLUDEPATH += ../common/include
INCLUDEPATH += ../remote_controller/include
INCLUDEPATH += ../network/include ../network/src network/include
INCLUDEPATH += ../configuration/include ../configuration/src configuration/include

LIBS += -lgmock -lgtest
LIBS += -L../libs -lremote_controller -lnetworktest -lconfigurationtest -lcommontest

SOURCES += test_main.cpp

DIR_PREFIX = ..

! include( ../remote_controller/public_files.pri ) {
    error( Couldnt find the remote_controller public_files.pri file! )
}

! include( ../remote_controller/private_files.pri ) {
    error( Couldnt find the remote_controller private_files.pri file! )
}

SOURCES += remote_controller/RemoteControllerTest.cpp

TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
