#ifndef CODEBASE_COMMANDHISTORY_MOCKS_H
#define CODEBASE_COMMANDHISTORY_MOCKS_H

#include "CBCommandHistory.h"

class CBCommandHistoryDummy;
typedef std::shared_ptr<CBCommandHistoryDummy> CBCommandHistoryDummyPtr;
class CBCommandHistoryDummy : public CBCommandHistory {
public:
    static CBCommandHistoryDummyPtr getNewInstance() {
        return CBCommandHistoryDummyPtr(new CBCommandHistoryDummy());
    };
    virtual ~CBCommandHistoryDummy() {};
protected:
    CBCommandHistoryDummy() {};
public:
    virtual void undo() {}
    virtual void redo() {}

    virtual bool undoIsPossible() { return false; }
    virtual bool redoIsPossible() { return false; }

    virtual void attach(std::shared_ptr<CBObserver> observer) {}
    virtual void detach(std::shared_ptr<CBObserver> observer) {}
};

class CBCommandHistoryStub;
typedef std::shared_ptr<CBCommandHistoryStub> CBCommandHistoryStubPtr;
class CBCommandHistoryStub : public CBCommandHistoryDummy {
public:
    static CBCommandHistoryStubPtr getNewInstance() {
        return CBCommandHistoryStubPtr(new CBCommandHistoryStub());
    };
    virtual ~CBCommandHistoryStub() {};
protected:
    CBCommandHistoryStub() {};
public:
    virtual bool undoIsPossible() { return undoPossible; };
    virtual void setUndoIsPossible(bool isPossible) { this->undoPossible = isPossible; }

    virtual bool redoIsPossible() { return redoPossible; };
    virtual void setRedoIsPossible(bool isPossible) { this->redoPossible = isPossible; }

private:
    bool undoPossible = false;
    bool redoPossible = false;
};

class CBCommandHistorySpy;
typedef std::shared_ptr<CBCommandHistorySpy> CBCommandHistorySpyPtr;
class CBCommandHistorySpy : public CBCommandHistoryStub {
public:
    static CBCommandHistorySpyPtr getNewInstance() {
        return CBCommandHistorySpyPtr(new CBCommandHistorySpy());
    }
    virtual  ~CBCommandHistorySpy() {}
protected:
    CBCommandHistorySpy() {}

public:
    virtual void undo() {
        undone = true;
    }
    virtual bool wasUndone() {
        return undone;
    }

    virtual void redo() {
        redone = true;
    }
    virtual bool wasRedone() {
        return redone;
    }

private:
    bool undone = false;
    bool redone = false;
};

#endif //CODEBASE_COMMANDHISTORY_MOCKS_H