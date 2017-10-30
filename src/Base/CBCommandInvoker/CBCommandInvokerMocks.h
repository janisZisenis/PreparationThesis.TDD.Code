#ifndef CODEBASE_COMMANDINVOKER_MOCKS_H
#define CODEBASE_COMMANDINVOKER_MOCKS_H

#include "CBCommandInvoker.h"

class CBCommandInvokerDummy;
typedef std::shared_ptr<CBCommandInvokerDummy> CBCommandInvokerDummyPtr;
class CBCommandInvokerDummy : public CBCommandInvoker {
public:
    static CBCommandInvokerDummyPtr getNewInstance() {
        return CBCommandInvokerDummyPtr(new CBCommandInvokerDummy());
    };
    virtual ~CBCommandInvokerDummy() {};
protected:
    CBCommandInvokerDummy() {};
public:
    virtual void invoke(std::shared_ptr<CBCommand> command) {};
};

class CBCommandInvokerSpy;
typedef std::shared_ptr<CBCommandInvokerSpy> CBCommandInvokerSpyPtr;
class CBCommandInvokerSpy : public CBCommandInvokerDummy {
public:
    static CBCommandInvokerSpyPtr getNewInstance() {
        return CBCommandInvokerSpyPtr(new CBCommandInvokerSpy());
    };

    virtual ~CBCommandInvokerSpy() {};
protected:
    CBCommandInvokerSpy() {};

public:
    virtual void invoke(std::shared_ptr<CBCommand> command) {
        invokedCommand = command;
    };
    virtual std::shared_ptr<CBCommand> getInvokedCommand() {
        return invokedCommand;
    }
private:
    std::shared_ptr<CBCommand> invokedCommand;
};

#endif //CODEBASE_COMMANDINVOKER_MOCKS_H