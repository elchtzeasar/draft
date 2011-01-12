TARGET = networktest

QT += network

! include( ../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

! include( ../include/files.pri ) {
    error( Couldnt find the network public_files.pri file! )
}

! include( ../src/files.pri ) {
    error( Couldnt find the network private_files.pri file! )
}


HEADERS += include/ConnectionMock.h
HEADERS += include/ConnectionListenerMock.h
HEADERS += include/NetworkComponentFactoryMock.h

SOURCES += NetworkComponentTest.cpp
