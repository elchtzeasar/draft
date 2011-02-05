DEFINES += "UI_TYPE=RemoteController"

! include(../main.pri) {
    error( Couldnt find the main.pri file! )
}

LIBS += -L/usr/local/include/glog -lglog

TARGET = ../../bin/console_draft
