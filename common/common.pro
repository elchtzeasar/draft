! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += include/AddressHeader.h
HEADERS += include/Message.h
HEADERS += include/NullMessage.h
HEADERS += include/PlayerNameCfgMessage.h
HEADERS += include/AddressedMessage.h

SOURCES += src/AddressHeader.cpp
SOURCES += src/Message.cpp
SOURCES += src/NullMessage.cpp
SOURCES += src/PlayerNameCfgMessage.cpp
SOURCES += src/AddressedMessage.cpp
