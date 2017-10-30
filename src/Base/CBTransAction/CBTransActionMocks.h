#ifndef CODEBASE_TRANSACTION_MOCKS_H
#define CODEBASE_TRANSACTION_MOCKS_H

#include "CBTransAction.h"

class CBTransActionDummy;
typedef std::shared_ptr<CBTransActionDummy> CBTransActionDummyPtr;
class CBTransActionDummy : public CBTransAction {
public:
    static CBTransActionDummyPtr getNewInstance() {
        return CBTransActionDummyPtr(new CBTransActionDummy());
    }
    virtual ~CBTransActionDummy() {}
protected:
    CBTransActionDummy() {}

public:
    virtual void execute() {};
};

class CBTransActionSpy;
typedef std::shared_ptr<CBTransActionSpy> CBTransActionSpyPtr;
class CBTransActionSpy : public CBTransActionDummy {
public:
    static CBTransActionSpyPtr getNewInstance() {
        return CBTransActionSpyPtr(new CBTransActionSpy());
    }
    virtual ~CBTransActionSpy() {}
protected:
    CBTransActionSpy() {}

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

#endif //CODEBASE_TRANSACTION_MOCKS_H
