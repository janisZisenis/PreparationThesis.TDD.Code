#ifndef CROSSNATIVE_FIXEDSTATE_H
#define CROSSNATIVE_FIXEDSTATE_H

#include "Base/CNTransActionAppearance/CNActionState.h"

class CNFixedState;
typedef std::shared_ptr<CNFixedState> CNFixedStatePtr;

class CNFixedState : public CNActionState {
public:
    static CNFixedStatePtr getNewInstance(CNActionStates state = OFF);
    virtual ~CNFixedState();
private:
    CNFixedState(CNActionStates state);

public:
    CNActionStates getState() override;

private:
    CNActionStates state;
};

#endif //CROSSNATIVE_FIXEDSTATE_H