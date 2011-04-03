TARGET = networkcomponenttest

QT += network

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

INCLUDEPATH += ../../../common/test/component

SOURCES += NetworkComponentTest.cpp

