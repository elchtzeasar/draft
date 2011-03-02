TEMPLATE = subdirs
CONFIG = ordered staticlib
# Ordered could probably be removed here if we move common parts into a lib...

SUBDIRS = console_draft gui_draft unit_tests component_tests
