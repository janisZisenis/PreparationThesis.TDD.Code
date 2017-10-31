#include "CNFixedState.h"

CNFixedStatePtr CNFixedState::getNewInstance(CNTransActionStateValues state) {
    return CNFixedStatePtr(new CNFixedState(state));
}

CNFixedState::~CNFixedState() {}

CNFixedState::CNFixedState(CNTransActionStateValues state) : state(state) {}

CNTransActionStateValues CNFixedState::getState() {
    return state;
}
