TEMPLATE = subdirs
SUBDIRS = gui remote_controller

# build must be last:
CONFIG += ordered staticlib
SUBDIRS += console_draft
SUBDIRS += gui_draft
SUBDIRS += unit_tests
