! include( ../test_main.pri ) {
    error( Couldnt find the test_main.pri file! )
}

LIBS += -lremote_controllerunittest -lnetworkunittest -lconfigurationunittest -lcommonunittest

TARGET = ../../bin/unit_tests
