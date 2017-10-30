#ifndef CODEBASE_COMMANDINVOKER_H
#define CODEBASE_COMMANDINVOKER_H

#include <memory>

class CBCommand;

class CBCommandInvoker;
typedef std::shared_ptr<CBCommandInvoker> CBCommandInvokerPtr;

class CBCommandInvoker {
public:
    virtual ~CBCommandInvoker() {};
protected:
    CBCommandInvoker() {};

public:
    virtual void invoke(std::shared_ptr<CBCommand> command) = 0;
};

#endif //CODEBASE_COMMANDINVOKER_H