! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += include/StateMachineComponent.h
HEADERS += include/State.h
HEADERS += include/ClientState.h

SOURCES += src/StateMachineComponent.cpp
SOURCES += src/State.cpp
SOURCES += src/ClientState.cpp
