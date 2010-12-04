DEFINES += "UI_TYPE=RemoteController"

! include(../main.pri) {
    error( Couldnt find the main.pri file! )
}

TARGET = ../../bin/console_draft
