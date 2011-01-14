INCLUDEPATH += /usr/src/boost_1_44_0

HEADERS += $${DIR_PREFIX}/configuration/src/ConfigurationLoader.h
HEADERS += $${DIR_PREFIX}/configuration/src/ConfigurationLoaderImpl.h
HEADERS += $${DIR_PREFIX}/configuration/src/PlayerContext.h
HEADERS += $${DIR_PREFIX}/configuration/src/PlayerContextImpl.h

SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationComponent.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationComponentFactory.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationLoaderImpl.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/PlayerContextImpl.cpp
