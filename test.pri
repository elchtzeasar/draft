# Stolen from http://stackoverflow.com/questions/1417776/how-to-use-qmakes-subdirs-template

# Includes common configuration for all subdirectory .pro files.

# Include test .h-files:
INCLUDEPATH += . ../include ../../../common/test/include
# Include 'real' .h-files:
INCLUDEPATH += ../../include ../../src
# Include common .h-files:
INCLUDEPATH += ../../../common/include

WARNINGS += -Wall

LIBS += -lgmock -lgtest

TEMPLATE = lib
#CONFIG += staticlib
QT += testlib

# Make sure qmake tracks dependencies:
CONFIG += create_prl debug

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = ../../mocs
DESTDIR = ../../../libs
OBJECTS_DIR = ../../objs

DIR_PREFIX = ../../..

! include( ../../include/files.pri ) {
    error( Couldnt find the public 'real' files.pri file! )
}

! include( ../../src/files.pri ) {
    error( Couldnt find the private 'real' files.pri file! )
}

! include( ../include/files.pri ) {
    warning( Couldnt find the public test files.pri file! )
}

! include( ../src/files.pri ) {
    warning( Couldnt find the private test files.pri file! )
}
