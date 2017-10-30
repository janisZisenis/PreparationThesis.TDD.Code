#ifndef CROSSNATIVE_UNDOACTION_H
#define CROSSNATIVE_UNDOACTION_H

#include "Base/CNTransAction/CNTransAction.h"

class CNCommandHistory;

class CNUndoAction;
typedef std::shared_ptr<CNUndoAction> CNUndoActionPtr;

class CNUndoAction : public CNTransAction {
public:
    static CNUndoActionPtr getNewInstance(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual ~CNUndoAction();
protected:
    CNUndoAction(std::shared_ptr<CNCommandHistory> commandHistory);

public:
    virtual void execute() override;

private:
    std::shared_ptr<CNCommandHistory> commandHistory;
};

#endif //CROSSNATIVE_UNDOACTION_H
