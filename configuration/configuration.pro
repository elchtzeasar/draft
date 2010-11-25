! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

INCLUDEPATH += /usr/src/boost_1_44_0

HEADERS += include/ConfigurationComponent.h
HEADERS += include/ConfigurationComponentFactory.h

HEADERS += src/ConfigurationManager.h
HEADERS += src/ConfigurationManagerImpl.h

SOURCES += src/ConfigurationComponent.cpp
SOURCES += src/ConfigurationComponentFactory.cpp
SOURCES += src/ConfigurationManagerImpl.cpp
