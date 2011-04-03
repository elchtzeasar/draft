! include( ../test_main.pri ) {
    error( Couldnt find the test_main.pri file! )
}

LIBS += -lcommoncomponenttest
LIBS += -lconfigurationcomponenttest
LIBS += -lnetworkcomponenttest
LIBS += -lstatecomponenttest
LIBS += -lcommon -lstate

TARGET = ../../bin/component_tests
