#ifndef CROSSNATIVE_FIXEDSTATE_H
#define CROSSNATIVE_FIXEDSTATE_H

#include "Base/TransActionAppearances/CNTransActionAppearanceImp/CNTransActionState.h"

class CNFixedState;
typedef std::shared_ptr<CNFixedState> CNFixedStatePtr;

class CNFixedState : public CNTransActionState {
public:
    static CNFixedStatePtr getNewInstance(CNTransActionStateValues state = OFF);
    virtual ~CNFixedState();
private:
    CNFixedState(CNTransActionStateValues state);

public:
    CNTransActionStateValues getState() override;

private:
    CNTransActionStateValues state;
};

#endif //CROSSNATIVE_FIXEDSTATE_H