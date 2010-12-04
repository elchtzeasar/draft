DEFINES += "UI_TYPE=Gui"

! include(../main.pri) {
    error( Couldnt find the main.pri file! )
}

TARGET = ../../bin/draft
