TEMPLATE = subdirs

SUBDIRS = sub_src sub_test

sub_src.subdir = src

sub_test.subdir = test
sub_test.depends = sub_src
