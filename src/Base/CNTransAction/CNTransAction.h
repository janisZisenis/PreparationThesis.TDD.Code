#ifndef CROSSNATIVE_TRANSACTION_H
#define CROSSNATIVE_TRANSACTION_H

#include <memory>

class CNTransAction;
typedef std::shared_ptr<CNTransAction> CNTransActionPtr;

class CNTransAction {
public:
    virtual ~CNTransAction() {}
protected:
    CNTransAction() {}

public:
    virtual void execute() = 0;
};

#endif //CROSSNATIVE_TRANSACTION_H
