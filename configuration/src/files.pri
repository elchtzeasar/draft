INCLUDEPATH += /usr/local/include/boost

HEADERS += $${DIR_PREFIX}/configuration/src/ConfigurationLoader.h
HEADERS += $${DIR_PREFIX}/configuration/src/ConfigurationLoaderImpl.h
HEADERS += $${DIR_PREFIX}/configuration/src/ConfigurationManager.h
HEADERS += $${DIR_PREFIX}/configuration/src/ConfigurationManagerImpl.h
HEADERS += $${DIR_PREFIX}/configuration/src/PlayerContext.h
HEADERS += $${DIR_PREFIX}/configuration/src/PlayerContextImpl.h
HEADERS += $${DIR_PREFIX}/configuration/src/PlayerContextFactory.h
HEADERS += $${DIR_PREFIX}/configuration/src/PlayerContextFactoryImpl.h

SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationComponent.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationComponentFactory.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationLoaderImpl.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/ConfigurationManagerImpl.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/PlayerContextImpl.cpp
SOURCES += $${DIR_PREFIX}/configuration/src/PlayerContextFactoryImpl.cpp
