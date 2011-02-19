TARGET = commoncomponenttest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

SOURCES += ConfigurationComponentStub.cpp
SOURCES += NetworkComponentStub.cpp
SOURCES += RemoteControllerStub.cpp
