#ifndef CROSSNATIVE_COMMANDINVOKER_TESTDOUBLES_H
#define CROSSNATIVE_COMMANDINVOKER_TESTDOUBLES_H

#include "CNCommandInvoker.h"

class CNCommandInvokerDummy;
typedef std::shared_ptr<CNCommandInvokerDummy> CNCommandInvokerDummyPtr;
class CNCommandInvokerDummy : public CNCommandInvoker {
public:
    static CNCommandInvokerDummyPtr getNewInstance() {
        return CNCommandInvokerDummyPtr(new CNCommandInvokerDummy());
    };
    virtual ~CNCommandInvokerDummy() {};
protected:
    CNCommandInvokerDummy() {};
public:
    virtual void invoke(std::shared_ptr<CNCommand> command) {};
};

class CNCommandInvokerSpy;
typedef std::shared_ptr<CNCommandInvokerSpy> CNCommandInvokerSpyPtr;
class CNCommandInvokerSpy : public CNCommandInvokerDummy {
public:
    static CNCommandInvokerSpyPtr getNewInstance() {
        return CNCommandInvokerSpyPtr(new CNCommandInvokerSpy());
    };

    virtual ~CNCommandInvokerSpy() {};
protected:
    CNCommandInvokerSpy() {};

public:
    virtual void invoke(std::shared_ptr<CNCommand> command) {
        invokedCommand = command;
    };
    virtual std::shared_ptr<CNCommand> getInvokedCommand() {
        return invokedCommand;
    }
private:
    std::shared_ptr<CNCommand> invokedCommand;
};

#endif //CROSSNATIVE_COMMANDINVOKER_TESTDOUBLES_H