#ifndef CODEBASEIMP_FIXEDSTATE_H
#define CODEBASEIMP_FIXEDSTATE_H

#include "Base/CBTransActionAppearance/CBActionState.h"

class CBFixedState;
typedef std::shared_ptr<CBFixedState> CBFixedStatePtr;

class CBFixedState : public CBActionState {
public:
    static CBFixedStatePtr getNewInstance(CBActionStates state = OFF);
    virtual ~CBFixedState();
private:
    CBFixedState(CBActionStates state);

public:
    CBActionStates getState() override;

private:
    CBActionStates state;
};

#endif //CODEBASEIMP_FIXEDSTATE_H