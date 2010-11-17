! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

INCLUDEPATH += /usr/src/boost_1_44_0

HEADERS += src/ConfigurationManager.h

SOURCES += src/ConfigurationManager.cpp
