#ifndef CROSSNATIVE_TRANSACTIONSTATE_TESTDOUBLES_H
#define CROSSNATIVE_TRANSACTIONSTATE_TESTDOUBLES_H

#include "CNTransActionState.h"

class CNTransActionStateDummy;
typedef std::shared_ptr<CNTransActionStateDummy> CNTransActionStateDummyPtr;
class CNTransActionStateDummy : public CNTransActionState {
public:
    static CNTransActionStateDummyPtr getNewInstance() {
        return CNTransActionStateDummyPtr(new CNTransActionStateDummy());
    }
    virtual ~CNTransActionStateDummy() {}
protected:
    CNTransActionStateDummy() {}

public:
    virtual CNTransActionStateValues getState() override { return OFF; };
};

class CNTransActionStateStub;
typedef std::shared_ptr<CNTransActionStateStub> CNTransActionStateStubPtr;
class CNTransActionStateStub : public CNTransActionStateDummy {
public:
    static CNTransActionStateStubPtr getNewInstance() {
        return CNTransActionStateStubPtr(new CNTransActionStateStub());
    }
    virtual ~CNTransActionStateStub() {}
protected:
    CNTransActionStateStub() {}

public:
    virtual CNTransActionStateValues getState() override { return state; };
    virtual void setState(CNTransActionStateValues state) {
        this->state = state;
    }

private:
    CNTransActionStateValues state;
};

#endif //CROSSNATIVE_TRANSACTIONSTATE_TESTDOUBLES_H