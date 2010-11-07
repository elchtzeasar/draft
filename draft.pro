TEMPLATE = subdirs
SUBDIRS = gui remote_control

# build must be last:
CONFIG += ordered staticlib
SUBDIRS += build
SUBDIRS += unit_tests
