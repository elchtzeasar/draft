TEMPLATE = subdirs
SUBDIRS = gui remote_controller common network configuration state

# build must be last:
CONFIG += ordered staticlib debug
SUBDIRS += main
SUBDIRS += unit_tests
