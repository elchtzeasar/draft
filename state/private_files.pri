HEADERS += ../state/src/State.h
HEADERS += ../state/src/SendingNameState.h
HEADERS += ../state/src/SavingPlayerNameState.h

SOURCES += ../state/src/StateMachineComponent.cpp
SOURCES += ../state/src/State.cpp
SOURCES += ../state/src/SendingNameState.cpp
SOURCES += ../state/src/SavingPlayerNameState.cpp

# Client states:
HEADERS += ../state/src/client/ClientState.h
HEADERS += ../state/src/client/ClientConfiguringState.h
HEADERS += ../state/src/client/SavingPlayerIdState.h

SOURCES += ../state/src/client/ClientState.cpp
SOURCES += ../state/src/client/ClientConfiguringState.cpp
SOURCES += ../state/src/client/SavingPlayerIdState.cpp

# Server states:
HEADERS += ../state/src/server/ServerState.h
HEADERS += ../state/src/server/ClientStateMachine.h
HEADERS += ../state/src/server/SendingPlayerIdState.h
HEADERS += ../state/src/server/ServerConfiguringState.h

SOURCES += ../state/src/server/ServerState.cpp
SOURCES += ../state/src/server/SendingPlayerIdState.cpp
SOURCES += ../state/src/server/ClientStateMachine.cpp
SOURCES += ../state/src/server/ServerConfiguringState.cpp
