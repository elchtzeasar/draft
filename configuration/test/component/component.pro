TARGET = configurationcomponenttest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

INCLUDEPATH += ../../../common/test/component

SOURCES += ConfigurationComponentTest.cpp
