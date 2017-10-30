#ifndef CROSSNATIVE_ACTIONSTATE_H
#define CROSSNATIVE_ACTIONSTATE_H

#include <memory>
#include <string>

#include "CNActionStates.h"

class CNActionState;
typedef std::shared_ptr<CNActionState> CNActionStatePtr;

class CNActionState {
public:
    virtual ~CNActionState() {};
protected:
    CNActionState() {};

public:
    virtual CNActionStates getState() = 0;
};

#endif //CROSSNATIVE_ACTIONSTATE_H