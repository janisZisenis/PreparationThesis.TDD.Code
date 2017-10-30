#ifndef CODEBASE_ACTIONSTATE_MOCKS_H
#define CODEBASE_ACTIONSTATE_MOCKS_H

#include "CBActionState.h"

class CBActionStateDummy;
typedef std::shared_ptr<CBActionStateDummy> CBActionStateDummyPtr;
class CBActionStateDummy : public CBActionState {
public:
    static CBActionStateDummyPtr getNewInstance() {
        return CBActionStateDummyPtr(new CBActionStateDummy());
    }
    virtual ~CBActionStateDummy() {}
protected:
    CBActionStateDummy() {}

public:
    virtual CBActionStates getState() override { return OFF; };
};

class CBActionStateStub;
typedef std::shared_ptr<CBActionStateStub> CBActionStateStubPtr;
class CBActionStateStub : public CBActionStateDummy {
public:
    static CBActionStateStubPtr getNewInstance() {
        return CBActionStateStubPtr(new CBActionStateStub());
    }
    virtual ~CBActionStateStub() {}
protected:
    CBActionStateStub() {}

public:
    virtual CBActionStates getState() override { return state; };
    virtual void setState(CBActionStates state) {
        this->state = state;
    }

private:
    CBActionStates state;
};

#endif //CODEBASE_ACTIONSTATE_MOCKS_H