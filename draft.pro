TEMPLATE = subdirs
SUBDIRS = gui remote_controller

# build must be last:
CONFIG += ordered staticlib
SUBDIRS += build
SUBDIRS += unit_tests
