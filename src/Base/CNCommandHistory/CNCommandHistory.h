#ifndef CROSSNATIVE_COMMANDHISTORY_H
#define CROSSNATIVE_COMMANDHISTORY_H

#include <memory>

class CNObserver;

class CNCommandHistory;
typedef std::shared_ptr<CNCommandHistory> CNCommandHistoryPtr;

class CNCommandHistory {
public:
    virtual ~CNCommandHistory() {};
protected:
    CNCommandHistory() {};

public:
    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual bool undoIsPossible() = 0;
    virtual bool redoIsPossible() = 0;

    virtual void attach(std::shared_ptr<CNObserver> observer) = 0;
    virtual void detach(std::shared_ptr<CNObserver> observer) = 0;
};

#endif //CROSSNATIVE_COMMANDHISTORY_H