! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

INCLUDEPATH += src/client src/server

HEADERS += include/StateMachineComponent.h

HEADERS += src/State.h
HEADERS += src/SendingNameState.h

SOURCES += src/StateMachineComponent.cpp
SOURCES += src/State.cpp
SOURCES += src/SendingNameState.cpp

# Client states:
HEADERS += src/client/ClientState.h
HEADERS += src/client/ClientConfiguringState.h

SOURCES += src/client/ClientState.cpp
SOURCES += src/client/ClientConfiguringState.cpp

# Server states:
HEADERS += src/server/ServerState.h
HEADERS += src/server/ClientStateMachine.h
HEADERS += src/server/ServerConfiguringState.h
HEADERS += src/server/WaitingForAllPlayersToConnectState.h

SOURCES += src/server/ServerState.cpp
SOURCES += src/server/ClientStateMachine.cpp
SOURCES += src/server/ServerConfiguringState.cpp
SOURCES += src/server/WaitingForAllPlayersToConnectState.cpp
