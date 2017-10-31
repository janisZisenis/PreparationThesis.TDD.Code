#ifndef CROSSNATIVE_REDOACTION_H
#define CROSSNATIVE_REDOACTION_H

#include "Base/CNTransAction/CNTransAction.h"

class CNCommandHistory;

class CNRedoAction;
typedef std::shared_ptr<CNRedoAction> CNRedoActionPtr;

class CNRedoAction : public CNTransAction {
public:
    static CNRedoActionPtr getNewInstance(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual ~CNRedoAction();
protected:
    CNRedoAction(std::shared_ptr<CNCommandHistory> commandHistory);

public:
    virtual void execute() override;

private:
    std::shared_ptr<CNCommandHistory> commandHistory;
};

#endif //CROSSNATIVE_REDOACTION_H
