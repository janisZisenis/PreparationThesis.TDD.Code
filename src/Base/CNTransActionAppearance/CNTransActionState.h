#ifndef CROSSNATIVE_TRANSACTIONSTATE_H
#define CROSSNATIVE_TRANSACTIONSTATE_H

#include <memory>
#include <string>

#include "CNTransActionStateValues.h"

class CNTransActionState;
typedef std::shared_ptr<CNTransActionState> CNTransActionStatePtr;

class CNTransActionState {
public:
    virtual ~CNTransActionState() {};
protected:
    CNTransActionState() {};

public:
    virtual CNTransActionStateValues getState() = 0;
};

#endif //CROSSNATIVE_TRANSACTIONSTATE_H