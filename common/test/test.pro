TARGET = commontest

! include( ../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

! include( ../include/files.pri ) {
    error( Couldnt find the common public_files.pri file! )
}

! include( ../src/files.pri ) {
    error( Couldnt find the common private_files.pri file! )
}

SOURCES += AddressHeaderTest.cpp
SOURCES += MessageTest.cpp
SOURCES += NullMessageTest.cpp
SOURCES += PlayerNameCfgMessageTest.cpp
