#ifndef CROSSNATIVE_NULLTRANSACTION_H
#define CROSSNATIVE_NULLTRANSACTION_H

#include "CNTransAction.h"

class CNNullTransAction;
typedef std::shared_ptr<CNNullTransAction> CNNullTransActionPtr;

class CNNullTransAction : public CNTransAction {
public:
    static CNNullTransActionPtr getNewInstance() {
        return CNNullTransActionPtr(new CNNullTransAction());
    }
    virtual ~CNNullTransAction() {}
protected:
    CNNullTransAction() {}

public:
    virtual void execute() override {}
};

#endif //CROSSNATIVE_NULLTRANSACTION_H
