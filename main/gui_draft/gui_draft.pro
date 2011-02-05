DEFINES += "UI_TYPE=Gui"

! include(../main.pri) {
    error( Couldnt find the main.pri file! )
}

LIBS += -L/usr/local/include/glog -lglog

TARGET = ../../bin/draft
