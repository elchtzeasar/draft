TARGET = commoncomponenttest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}


HEADERS += ConfigurationComponentStub.h
HEADERS += NetworkComponentStub.h
HEADERS += RemoteControllerStub.h

SOURCES += ConfigurationComponentStub.cpp
SOURCES += NetworkComponentStub.cpp
SOURCES += RemoteControllerStub.cpp
