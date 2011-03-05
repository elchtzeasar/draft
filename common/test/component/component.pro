TARGET = commoncomponenttest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}


HEADERS += ConfigurationComponentStub.h
HEADERS += NetworkComponentStub.h
HEADERS += RemoteControllerStub.h
HEADERS += SignalWaiter.h
HEADERS += StateChangeWaiter.h

SOURCES += ConfigurationComponentStub.cpp
SOURCES += NetworkComponentStub.cpp
SOURCES += RemoteControllerStub.cpp
SOURCES += SignalWaiter.cpp
SOURCES += StateChangeWaiter.cpp
