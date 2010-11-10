! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

QT += network

HEADERS += include/NetworkComponent.h

HEADERS += src/Connection.h
HEADERS += src/ConnectionListener.h

SOURCES += src/NetworkComponent.cpp
SOURCES += src/Connection.cpp
SOURCES += src/ConnectionListener.cpp

