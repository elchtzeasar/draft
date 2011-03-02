TEMPLATE = subdirs
CONFIG += staticlib debug

SUBLIBS = sub_gui sub_remote_controller sub_common sub_network sub_configuration sub_state

SUBDIRS = sub_gui sub_remote_controller sub_common sub_network sub_configuration sub_state main_app

sub_gui.subdir = gui
sub_remote_controller.subdir = remote_controller
sub_common.subdir = common
sub_network.subdir = network
sub_configuration.subdir = configuration
sub_state.subdir = state

main_app.subdir = main
main_app.depends = sub_gui sub_remote_controller sub_common sub_network sub_configuration sub_state
