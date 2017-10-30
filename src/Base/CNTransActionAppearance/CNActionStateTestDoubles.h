#ifndef CROSSNATIVE_ACTIONSTATE_MOCKS_H
#define CROSSNATIVE_ACTIONSTATE_MOCKS_H

#include "CNActionState.h"

class CNActionStateDummy;
typedef std::shared_ptr<CNActionStateDummy> CNActionStateDummyPtr;
class CNActionStateDummy : public CNActionState {
public:
    static CNActionStateDummyPtr getNewInstance() {
        return CNActionStateDummyPtr(new CNActionStateDummy());
    }
    virtual ~CNActionStateDummy() {}
protected:
    CNActionStateDummy() {}

public:
    virtual CNActionStates getState() override { return OFF; };
};

class CNActionStateStub;
typedef std::shared_ptr<CNActionStateStub> CNActionStateStubPtr;
class CNActionStateStub : public CNActionStateDummy {
public:
    static CNActionStateStubPtr getNewInstance() {
        return CNActionStateStubPtr(new CNActionStateStub());
    }
    virtual ~CNActionStateStub() {}
protected:
    CNActionStateStub() {}

public:
    virtual CNActionStates getState() override { return state; };
    virtual void setState(CNActionStates state) {
        this->state = state;
    }

private:
    CNActionStates state;
};

#endif //CROSSNATIVE_ACTIONSTATE_MOCKS_H