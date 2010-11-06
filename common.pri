# Stolen from http://stackoverflow.com/questions/1417776/how-to-use-qmakes-subdirs-template

#Includes common configuration for all subdirectory .pro files.
INCLUDEPATH += . ..
WARNINGS += -Wall

TEMPLATE = lib
CONFIG += staticlib

# The following keeps the generated files at least somewhat separate 
# from the source files.
MOC_DIR = mocs
DESTDIR = ../libs
OBJECTS_DIR = objs
