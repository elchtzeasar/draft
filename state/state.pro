! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += include/StateMachineComponent.h

HEADERS += src/State.h
HEADERS += src/ClientState.h
HEADERS += src/ClientConfiguringState.h
HEADERS += src/ServerState.h
HEADERS += src/ClientStateMachine.h

SOURCES += src/StateMachineComponent.cpp
SOURCES += src/State.cpp
SOURCES += src/ClientState.cpp
SOURCES += src/ClientConfiguringState.cpp
SOURCES += src/ServerState.cpp
SOURCES += src/ClientStateMachine.cpp
