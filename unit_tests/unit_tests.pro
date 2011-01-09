TEMPLATE = app

QT += testlib network
CONFIG += link_prl

INCLUDEPATH += ../common/include
INCLUDEPATH += ../remote_controller/include
INCLUDEPATH += ../network/include ../network/src network/include
INCLUDEPATH += ../configuration/include ../configuration/src configuration/include

LIBS += -lgmock -lgtest
LIBS += -L../libs -lremote_controller -lnetwork -lconfiguration -lcommon

SOURCES += test_main.cpp

HEADERS += network/include/ConnectionMock.h
HEADERS += network/include/ConnectionListenerMock.h
HEADERS += network/include/NetworkComponentFactoryMock.h

SOURCES += network/NetworkComponentTest.cpp

SOURCES += remote_controller/RemoteControllerTest.cpp

HEADERS += configuration/include/ConfigurationLoaderMock.h
HEADERS += configuration/include/ConfigurationManagerMock.h
SOURCES += configuration/ConfigurationComponentTest.cpp
SOURCES += configuration/ConfigurationLoaderTest.cpp

SOURCES += common/AddressHeaderTest.cpp
SOURCES += common/MessageTest.cpp
SOURCES += common/NullMessageTest.cpp
SOURCES += common/PlayerNameCfgMessageTest.cpp

TARGET = ../bin/unit_tests

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
