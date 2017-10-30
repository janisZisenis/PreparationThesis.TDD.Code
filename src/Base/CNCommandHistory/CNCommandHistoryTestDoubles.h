#ifndef CROSSNATIVE_COMMANDHISTORY_TESTDOUBLES_H
#define CROSSNATIVE_COMMANDHISTORY_TESTDOUBLES_H

#include "CNCommandHistory.h"

class CNCommandHistoryDummy;
typedef std::shared_ptr<CNCommandHistoryDummy> CNCommandHistoryDummyPtr;
class CNCommandHistoryDummy : public CNCommandHistory {
public:
    static CNCommandHistoryDummyPtr getNewInstance() {
        return CNCommandHistoryDummyPtr(new CNCommandHistoryDummy());
    };
    virtual ~CNCommandHistoryDummy() {};
protected:
    CNCommandHistoryDummy() {};
public:
    virtual void undo() {}
    virtual void redo() {}

    virtual bool undoIsPossible() { return false; }
    virtual bool redoIsPossible() { return false; }

    virtual void attach(std::shared_ptr<CNObserver> observer) {}
    virtual void detach(std::shared_ptr<CNObserver> observer) {}
};

class CNCommandHistoryStub;
typedef std::shared_ptr<CNCommandHistoryStub> CNCommandHistoryStubPtr;
class CNCommandHistoryStub : public CNCommandHistoryDummy {
public:
    static CNCommandHistoryStubPtr getNewInstance() {
        return CNCommandHistoryStubPtr(new CNCommandHistoryStub());
    };
    virtual ~CNCommandHistoryStub() {};
protected:
    CNCommandHistoryStub() {};
public:
    virtual bool undoIsPossible() { return undoPossible; };
    virtual void setUndoIsPossible(bool isPossible) { this->undoPossible = isPossible; }

    virtual bool redoIsPossible() { return redoPossible; };
    virtual void setRedoIsPossible(bool isPossible) { this->redoPossible = isPossible; }

private:
    bool undoPossible = false;
    bool redoPossible = false;
};

class CNCommandHistorySpy;
typedef std::shared_ptr<CNCommandHistorySpy> CNCommandHistorySpyPtr;
class CNCommandHistorySpy : public CNCommandHistoryStub {
public:
    static CNCommandHistorySpyPtr getNewInstance() {
        return CNCommandHistorySpyPtr(new CNCommandHistorySpy());
    }
    virtual  ~CNCommandHistorySpy() {}
protected:
    CNCommandHistorySpy() {}

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

#endif //CROSSNATIVE_COMMANDHISTORY_TESTDOUBLES_H