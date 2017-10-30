#include "CNFixedState.h"

CNFixedStatePtr CNFixedState::getNewInstance(CNActionStates state) {
    return CNFixedStatePtr(new CNFixedState(state));
}

CNFixedState::~CNFixedState() {}

CNFixedState::CNFixedState(CNActionStates state) : state(state) {}

CNActionStates CNFixedState::getState() {
    return state;
}
