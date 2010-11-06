! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

HEADERS += src/MainWindow.h
HEADERS += src/FileMenu.h
HEADERS += src/HostDraftDialog.h

SOURCES += src/MainWindow.cpp
SOURCES += src/FileMenu.cpp
SOURCES += src/HostDraftDialog.cpp
