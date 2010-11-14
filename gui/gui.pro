! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += include/Gui.h

HEADERS += src/FileMenu.h
HEADERS += src/HostDraftDialog.h
HEADERS += src/ConnectToDraftDialog.h
HEADERS += src/MainWindow.h

SOURCES += src/Gui.cpp
SOURCES += src/MainWindow.cpp
SOURCES += src/FileMenu.cpp
SOURCES += src/HostDraftDialog.cpp
SOURCES += src/ConnectToDraftDialog.cpp
