TEMPLATE = subdirs
SUBDIRS = gui remote_controller network configuration

# build must be last:
CONFIG += ordered staticlib
SUBDIRS += main
SUBDIRS += unit_tests
