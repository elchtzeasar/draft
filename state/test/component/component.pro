TARGET = statecomponenttest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

SOURCES += StateComponentSinglePlayerConnectionTest.cpp