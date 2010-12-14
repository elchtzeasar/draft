! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += include/AddressHeader.h
HEADERS += include/Message.h
HEADERS += include/NullMessage.h
HEADERS += include/AddressedMessage.h

SOURCES += src/AddressHeader.cpp
SOURCES += src/NullMessage.cpp
SOURCES += src/AddressedMessage.cpp
