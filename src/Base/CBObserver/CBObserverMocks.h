#ifndef CODEBASE_OBSERVER_MOCKS_H
#define CODEBASE_OBSERVER_MOCKS_H

#include "CBObserver.h"

class CBObserverDummy;
typedef std::shared_ptr<CBObserverDummy> CBObserverDummyPtr;
class CBObserverDummy : public CBObserver {
public:
    static CBObserverDummyPtr getNewInstance() {
        return CBObserverDummyPtr(new CBObserverDummy());
    }
    virtual ~CBObserverDummy() {}

protected:
    CBObserverDummy() {}

public:
    virtual void update() {};
};

class CBObserverSpy;
typedef std::shared_ptr<CBObserverSpy> CBObserverSpyPtr;
class CBObserverSpy : public CBObserverDummy {
public:
    static CBObserverSpyPtr getNewInstance() {
        return CBObserverSpyPtr(new CBObserverSpy());
    }
    virtual ~CBObserverSpy() {}

protected:
    CBObserverSpy() {}

public:
    virtual void update() {
        updated = true;
    }

    virtual bool wasUpdated() {
        return updated;
    }

private:
    bool updated = false;
};

#endif //CODEBASE_OBSERVER_MOCKS_H