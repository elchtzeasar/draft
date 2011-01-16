HEADERS += $${DIR_PREFIX}/state/src/State.h
HEADERS += $${DIR_PREFIX}/state/src/SendingNameState.h
HEADERS += $${DIR_PREFIX}/state/src/SavingPlayerNameState.h
HEADERS += $${DIR_PREFIX}/state/src/ReceivedMessageTransition.h

SOURCES += $${DIR_PREFIX}/state/src/StateMachineComponent.cpp
SOURCES += $${DIR_PREFIX}/state/src/State.cpp
SOURCES += $${DIR_PREFIX}/state/src/SendingNameState.cpp
SOURCES += $${DIR_PREFIX}/state/src/SavingPlayerNameState.cpp
SOURCES += $${DIR_PREFIX}/state/src/ReceivedMessageTransition.cpp

# Client states:
HEADERS += $${DIR_PREFIX}/state/src/client/ClientState.h
HEADERS += $${DIR_PREFIX}/state/src/client/ClientConfiguringState.h
HEADERS += $${DIR_PREFIX}/state/src/client/SavingPlayerIdState.h

SOURCES += $${DIR_PREFIX}/state/src/client/ClientState.cpp
SOURCES += $${DIR_PREFIX}/state/src/client/ClientConfiguringState.cpp
SOURCES += $${DIR_PREFIX}/state/src/client/SavingPlayerIdState.cpp

# Server states:
HEADERS += $${DIR_PREFIX}/state/src/server/ServerState.h
HEADERS += $${DIR_PREFIX}/state/src/server/ClientStateMachine.h
HEADERS += $${DIR_PREFIX}/state/src/server/SendingPlayerIdState.h
HEADERS += $${DIR_PREFIX}/state/src/server/ServerConfiguringState.h

SOURCES += $${DIR_PREFIX}/state/src/server/ServerState.cpp
SOURCES += $${DIR_PREFIX}/state/src/server/SendingPlayerIdState.cpp
SOURCES += $${DIR_PREFIX}/state/src/server/ClientStateMachine.cpp
SOURCES += $${DIR_PREFIX}/state/src/server/ServerConfiguringState.cpp
