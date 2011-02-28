# Stolen from http://stackoverflow.com/questions/1417776/how-to-use-qmakes-subdirs-template

# Includes common configuration for all subdirectory .pro files.

INCLUDEPATH += . ../include ../../common/include
WARNINGS += -Wall

TEMPLATE = lib
CONFIG += staticlib

# Make sure qmake tracks dependencies:
CONFIG += create_prl debug

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = ../mocs
DESTDIR = ../../libs
QMAKE_RPATH = $DESTDIR
OBJECTS_DIR = ../objs

DIR_PREFIX = ../..
