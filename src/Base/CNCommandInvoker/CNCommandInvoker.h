#ifndef CROSSNATIVE_COMMANDINVOKER_H
#define CROSSNATIVE_COMMANDINVOKER_H

#include <memory>

class CNCommand;

class CNCommandInvoker;
typedef std::shared_ptr<CNCommandInvoker> CNCommandInvokerPtr;

class CNCommandInvoker {
public:
    virtual ~CNCommandInvoker() {};
protected:
    CNCommandInvoker() {};

public:
    virtual void invoke(std::shared_ptr<CNCommand> command) = 0;
};

#endif //CROSSNATIVE_COMMANDINVOKER_H