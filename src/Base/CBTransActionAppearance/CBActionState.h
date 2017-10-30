#ifndef CODEBASE_ACTIONSTATE_H
#define CODEBASE_ACTIONSTATE_H

#include <memory>
#include <string>

#include "CBActionStates.h"

class CBActionState;
typedef std::shared_ptr<CBActionState> CBActionStatePtr;

class CBActionState {
public:
    virtual ~CBActionState() {};
protected:
    CBActionState() {};

public:
    virtual CBActionStates getState() = 0;
};

#endif //CODEBASE_ACTIONSTATE_H