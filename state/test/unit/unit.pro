TARGET = stateunittest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

HEADERS += StateMachineComponentStub.h
SOURCES += StateMachineComponentStub.cpp

SOURCES += StateTest.cpp
