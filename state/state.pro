! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += include/StateMachineComponent.h

HEADERS += src/State.h
SOURCES += src/StateMachineComponent.cpp
SOURCES += src/State.cpp

# Client states:
HEADERS += src/ClientState.h
HEADERS += src/ClientConfiguringState.h
HEADERS += src/SendingNameState.h

SOURCES += src/ClientState.cpp
SOURCES += src/ClientConfiguringState.cpp
SOURCES += src/SendingNameState.cpp

# Server states:
HEADERS += src/ServerState.h
HEADERS += src/ClientStateMachine.h
HEADERS += src/ServerConfiguringState.h
HEADERS += src/WaitingForAllPlayersToConnectState.h

SOURCES += src/ServerState.cpp
SOURCES += src/ClientStateMachine.cpp
SOURCES += src/ServerConfiguringState.cpp
SOURCES += src/WaitingForAllPlayersToConnectState.cpp
