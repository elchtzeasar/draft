TARGET = configurationunittest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

SOURCES += ConfigurationComponentTest.cpp
SOURCES += ConfigurationLoaderTest.cpp
SOURCES += ConfigurationManagerTest.cpp
