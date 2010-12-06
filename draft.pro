TEMPLATE = subdirs
SUBDIRS = gui remote_controller network configuration state

# build must be last:
CONFIG += ordered staticlib
SUBDIRS += main
SUBDIRS += unit_tests
