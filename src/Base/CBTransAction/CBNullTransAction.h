#ifndef CODEBASE_NULLTRANSACTION_H
#define CODEBASE_NULLTRANSACTION_H

#include "CBTransAction.h"

class CBNullTransAction;
typedef std::shared_ptr<CBNullTransAction> CBNullTransActionPtr;

class CBNullTransAction : public CBTransAction {
public:
    static CBNullTransActionPtr getNewInstance() {
        return CBNullTransActionPtr(new CBNullTransAction());
    }
    virtual ~CBNullTransAction() {}
protected:
    CBNullTransAction() {}

public:
    virtual void execute() override {}
};

#endif //CODEBASE_NULLTRANSACTION_H
