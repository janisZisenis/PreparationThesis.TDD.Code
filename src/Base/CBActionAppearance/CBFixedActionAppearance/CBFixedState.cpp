#include "CBFixedState.h"

CBFixedStatePtr CBFixedState::getNewInstance(CBActionStates state) {
    return CBFixedStatePtr(new CBFixedState(state));
}

CBFixedState::~CBFixedState() {}

CBFixedState::CBFixedState(CBActionStates state) : state(state) {}

CBActionStates CBFixedState::getState() {
    return state;
}
