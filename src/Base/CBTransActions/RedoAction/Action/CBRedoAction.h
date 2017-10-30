#ifndef CODEBASEIMP_REDOACTION_H
#define CODEBASEIMP_REDOACTION_H

#include "Base/CBTransAction/CBTransAction.h"

class CBCommandHistory;

class CBRedoAction;
typedef std::shared_ptr<CBRedoAction> CBRedoActionPtr;

class CBRedoAction : public CBTransAction {
public:
    static CBRedoActionPtr getNewInstance(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual ~CBRedoAction();
protected:
    CBRedoAction(std::shared_ptr<CBCommandHistory> commandHistory);

public:
    virtual void execute() override;

private:
    std::shared_ptr<CBCommandHistory> commandHistory;
};

#endif //CODEBASEIMP_REDOACTION_H
