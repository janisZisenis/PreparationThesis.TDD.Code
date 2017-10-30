#ifndef CODEBASE_COMMANDHISTORY_H
#define CODEBASE_COMMANDHISTORY_H

#include <memory>

class CBObserver;

class CBCommandHistory;
typedef std::shared_ptr<CBCommandHistory> CBCommandHistoryPtr;

class CBCommandHistory {
public:
    virtual ~CBCommandHistory() {};
protected:
    CBCommandHistory() {};

public:
    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual bool undoIsPossible() = 0;
    virtual bool redoIsPossible() = 0;

    virtual void attach(std::shared_ptr<CBObserver> observer) = 0;
    virtual void detach(std::shared_ptr<CBObserver> observer) = 0;
};

#endif //CODEBASE_COMMANDHISTORY_H