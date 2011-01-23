TARGET = configurationtest

! include( ../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

! include( ../include/files.pri ) {
    error( Couldnt find the configuration public_files.pri file! )
}

! include( ../src/files.pri ) {
    error( Couldnt find the configuration private_files.pri file! )
}

HEADERS += include/ConfigurationLoaderMock.h
HEADERS += include/PlayerContextMock.h
HEADERS += include/PlayerContextFactoryMock.h
SOURCES += src/PlayerContextMock.cpp

SOURCES += ConfigurationComponentTest.cpp
SOURCES += ConfigurationLoaderTest.cpp
SOURCES += ConfigurationManagerTest.cpp
