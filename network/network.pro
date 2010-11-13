! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

QT += network

HEADERS += include/NetworkComponent.h

HEADERS += src/Connection.h
HEADERS += src/ConnectionImpl.h
HEADERS += src/ConnectionListener.h
HEADERS += src/ConnectionListenerImpl.h

SOURCES += src/NetworkComponent.cpp
SOURCES += src/ConnectionImpl.cpp
SOURCES += src/ConnectionListenerImpl.cpp

