#ifndef CODEBASEIMP_UNDOACTION_H
#define CODEBASEIMP_UNDOACTION_H

#include "Base/CBTransAction/CBTransAction.h"

class CBCommandHistory;

class CBUndoAction;
typedef std::shared_ptr<CBUndoAction> CBUndoActionPtr;

class CBUndoAction : public CBTransAction {
public:
    static CBUndoActionPtr getNewInstance(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual ~CBUndoAction();
protected:
    CBUndoAction(std::shared_ptr<CBCommandHistory> commandHistory);

public:
    virtual void execute() override;

private:
    std::shared_ptr<CBCommandHistory> commandHistory;
};

#endif //CODEBASEIMP_UNDOACTION_H
