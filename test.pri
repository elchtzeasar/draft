# Stolen from http://stackoverflow.com/questions/1417776/how-to-use-qmakes-subdirs-template

# Includes common configuration for all subdirectory .pro files.

INCLUDEPATH += . include ../include ../src ../../common/include
WARNINGS += -Wall

LIBS += -lgmock -lgtest

TEMPLATE = lib
#CONFIG += staticlib
QT += testlib

# Make sure qmake tracks dependencies:
CONFIG += create_prl debug

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = ../mocs
DESTDIR = ../../libs
OBJECTS_DIR = ../objs

DIR_PREFIX = ../..