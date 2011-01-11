TEMPLATE = app

QT += testlib network
CONFIG += link_prl

INCLUDEPATH += ../common/include
INCLUDEPATH += ../remote_controller/include
INCLUDEPATH += ../network/include ../network/src network/include
INCLUDEPATH += ../configuration/include ../configuration/src configuration/include

LIBS += -lgmock -lgtest
LIBS += -L../libs -lremote_controller -lnetwork -lconfiguration -lcommon

SOURCES += test_main.cpp

! include( ../network/public_files.pri ) {
    error( Couldnt find the network public_files.pri file! )
}

! include( ../network/private_files.pri ) {
    error( Couldnt find the network private_files.pri file! )
}

HEADERS += network/include/ConnectionMock.h
HEADERS += network/include/ConnectionListenerMock.h
HEADERS += network/include/NetworkComponentFactoryMock.h

SOURCES += network/NetworkComponentTest.cpp

! include( ../remote_controller/public_files.pri ) {
    error( Couldnt find the remote_controller public_files.pri file! )
}

! include( ../remote_controller/private_files.pri ) {
    error( Couldnt find the remote_controller private_files.pri file! )
}

SOURCES += remote_controller/RemoteControllerTest.cpp

! include( ../configuration/public_files.pri ) {
    error( Couldnt find the configuration public_files.pri file! )
}

! include( ../configuration/private_files.pri ) {
    error( Couldnt find the configuration private_files.pri file! )
}

HEADERS += configuration/include/ConfigurationLoaderMock.h
HEADERS += configuration/include/ConfigurationManagerMock.h
SOURCES += configuration/ConfigurationComponentTest.cpp
SOURCES += configuration/ConfigurationLoaderTest.cpp

! include( ../common/public_files.pri ) {
    error( Couldnt find the common public_files.pri file! )
}

! include( ../common/private_files.pri ) {
    error( Couldnt find the common private_files.pri file! )
}

SOURCES += common/AddressHeaderTest.cpp
SOURCES += common/MessageTest.cpp
SOURCES += common/NullMessageTest.cpp
SOURCES += common/PlayerNameCfgMessageTest.cpp

TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
