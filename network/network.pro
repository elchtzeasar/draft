! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

QT += network

HEADERS += include/NetworkComponent.h
HEADERS += include/NetworkComponentFactory.h
HEADERS += include/NetworkComponentFactoryImpl.h

HEADERS += src/Connection.h
HEADERS += src/ConnectionImpl.h
HEADERS += src/ConnectionListener.h
HEADERS += src/ConnectionListenerImpl.h

SOURCES += src/NetworkComponentFactoryImpl.cpp
SOURCES += src/NetworkComponent.cpp
SOURCES += src/ConnectionImpl.cpp
SOURCES += src/ConnectionListenerImpl.cpp

