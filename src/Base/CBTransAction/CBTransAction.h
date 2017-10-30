#ifndef CODEBASE_TRANSACTION_H
#define CODEBASE_TRANSACTION_H

#include <memory>

class CBTransAction;
typedef std::shared_ptr<CBTransAction> CBTransActionPtr;

class CBTransAction {
public:
    virtual ~CBTransAction() {}
protected:
    CBTransAction() {}

public:
    virtual void execute() = 0;
};

#endif //CODEBASE_TRANSACTION_H
