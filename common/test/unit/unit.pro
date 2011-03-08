TARGET = commonunittest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

SOURCES += AddressHeaderTest.cpp
SOURCES += MessageTest.cpp
SOURCES += NullMessageTest.cpp
SOURCES += PlayerConfigurationCfgMessageTest.cpp
