TARGET = networkunittest

QT += network

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

SOURCES += NetworkComponentTest.cpp
