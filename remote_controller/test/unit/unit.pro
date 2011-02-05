TARGET = remote_controllerunittest

! include( ../../../test.pri ) {
    error( Couldnt find the test.pri file! )
}

SOURCES += RemoteControllerTest.cpp
