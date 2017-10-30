#ifndef CROSSNATIVE_TRANSACTION_MOCKS_H
#define CROSSNATIVE_TRANSACTION_MOCKS_H

#include "CNTransAction.h"

class CNTransActionDummy;
typedef std::shared_ptr<CNTransActionDummy> CNTransActionDummyPtr;
class CNTransActionDummy : public CNTransAction {
public:
    static CNTransActionDummyPtr getNewInstance() {
        return CNTransActionDummyPtr(new CNTransActionDummy());
    }
    virtual ~CNTransActionDummy() {}
protected:
    CNTransActionDummy() {}

public:
    virtual void execute() {};
};

class CNTransActionSpy;
typedef std::shared_ptr<CNTransActionSpy> CNTransActionSpyPtr;
class CNTransActionSpy : public CNTransActionDummy {
public:
    static CNTransActionSpyPtr getNewInstance() {
        return CNTransActionSpyPtr(new CNTransActionSpy());
    }
    virtual ~CNTransActionSpy() {}
protected:
    CNTransActionSpy() {}

public:
    virtual void execute() {
        executed = true;
    };
    virtual bool wasExecuted() {
        return executed;
    }

private:
    bool executed = false;
};

#endif //CROSSNATIVE_TRANSACTION_MOCKS_H
