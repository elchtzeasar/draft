TEMPLATE = subdirs
SUBDIRS = gui

# build must be last:
CONFIG += ordered staticlib
SUBDIRS += build
SUBDIRS += unit_tests
