#include "State.h"
#include "StateMachineComponentStub.h"

#include <QObject>
#include <QSignalSpy>
#include <QStateMachine>
#include <QTest>
#include <QVariant>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

using std::string;
using std::stringstream;

class StateTest : public testing::Test {
protected:
    StateTest();
    ~StateTest();

    void createStateWithParent();
    void createStateWithoutParent();
    void addStateToStateMachine();
    void setPropertyInParent();

    StateMachineComponentStub component;
    State parent;
    State* state;
    QStateMachine* stateMachine;
    static const char* NAME;
    static const char* PARENT_NAME;
    static const char* PROPERTY_NAME;
    static const QVariant PROPERTY_VALUE;
    static const int MAX_WAIT;
};

StateTest::StateTest() :
    parent(&component, NULL, PARENT_NAME, false),
    state(NULL),
    stateMachine(NULL) {
}

StateTest::~StateTest() {
    if (stateMachine != NULL)
        delete stateMachine;
    else
        delete state;
}
    
void StateTest::createStateWithParent() {
    state = new State(&component, &parent, NAME, true);
}

void StateTest::createStateWithoutParent() {
    state = new State(&component, NULL, NAME, true);
}

void StateTest::addStateToStateMachine() {
    stateMachine = new QStateMachine;
    
    stateMachine->addState(state);
    stateMachine->setInitialState(state);

    stateMachine->start();
}

TEST_F(StateTest, shouldPrependOwnNameWithParentNameOnGetNameWithParent) {
    createStateWithParent();

    stringstream expectedName;
    expectedName << PARENT_NAME << "::" << NAME;
    
    ASSERT_EQ(state->getName().toStdString(), expectedName.str());
}

TEST_F(StateTest, shouldUseOwnNameOnGetNameWithoutParent) {
    createStateWithoutParent();

    ASSERT_EQ(state->getName().toStdString(), string(NAME));
}

TEST_F(StateTest, shouldSearchForPropertyInParentOnFindPropertyWhenStateHasNoProperty) {
    createStateWithParent();
    parent.setProperty(PROPERTY_NAME, PROPERTY_VALUE);

    ASSERT_EQ(PROPERTY_VALUE.toInt(),
              state->findProperty(PROPERTY_NAME).toInt());
}

TEST_F(StateTest, shouldSetPropertyInParentOnFindAndSetPropertyWhenStateHasNoProperty) {
    const QVariant NEW_PROPERTY_VALUE(666);
    createStateWithParent();
    parent.setProperty(PROPERTY_NAME, PROPERTY_VALUE);

    state->findAndSetProperty(PROPERTY_NAME, NEW_PROPERTY_VALUE);

    ASSERT_EQ(NEW_PROPERTY_VALUE.toInt(),
              parent.findProperty(PROPERTY_NAME).toInt());
}

TEST_F(StateTest, shouldGetPropertyFromSelfOnFindPropertyWhenStateHasProperty) {
    createStateWithParent();
    state->setProperty(PROPERTY_NAME, PROPERTY_VALUE);

    ASSERT_EQ(PROPERTY_VALUE.toInt(),
              state->findProperty(PROPERTY_NAME).toInt());
}

TEST_F(StateTest, shouldSetPropertyInSelfOnFindAndSetPropertyWhenStateHasProperty) {
    const QVariant NEW_PROPERTY_VALUE(666);
    createStateWithParent();
    state->setProperty(PROPERTY_NAME, PROPERTY_VALUE);

    state->findAndSetProperty(PROPERTY_NAME, NEW_PROPERTY_VALUE);

    ASSERT_EQ(NEW_PROPERTY_VALUE.toInt(),
              state->findProperty(PROPERTY_NAME).toInt());
}

TEST_F(StateTest, shouldSetNameInComponentWhenStateEntered) {
    const string expectedActiveState(NAME);
    createStateWithoutParent();

    addStateToStateMachine();

    for (int waits = 0; waits < MAX_WAIT; ++waits) {
        QTest::qWait(1);
        if (component.property("activeState").toString().toStdString() == expectedActiveState)
            break;
    }
    
    ASSERT_EQ(expectedActiveState,
              component.property("activeState").toString().toStdString());
              
}
const char* StateTest::NAME("[state name]");
const char* StateTest::PARENT_NAME("[parent name]");
const char* StateTest::PROPERTY_NAME("[property name]");
const QVariant StateTest::PROPERTY_VALUE(101);
const int StateTest::MAX_WAIT=100;
