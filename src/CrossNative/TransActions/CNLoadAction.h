#ifndef CROSSNATIVE_LOADACTION_H
#define CROSSNATIVE_LOADACTION_H

#include <CodeBase/CBTransAction/CBTransAction.h>

class CNLoadAction;
typedef std::shared_ptr<CNLoadAction> CNLoadActionPtr;

class CNLoadAction : public CBTransAction {
public:
    static CNLoadActionPtr getNewInstance();
    virtual ~CNLoadAction();
protected:
    CNLoadAction();
};

#endif //CROSSNATIVE_LOADACTION_H