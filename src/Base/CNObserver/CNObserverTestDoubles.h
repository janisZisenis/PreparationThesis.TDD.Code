#ifndef CROSSNATIVE_OBSERVER_TESTDOUBLES_H
#define CROSSNATIVE_OBSERVER_TESTDOUBLES_H

#include "CNObserver.h"

class CNObserverDummy;
typedef std::shared_ptr<CNObserverDummy> CNObserverDummyPtr;
class CNObserverDummy : public CNObserver {
public:
    static CNObserverDummyPtr getNewInstance() {
        return CNObserverDummyPtr(new CNObserverDummy());
    }
    virtual ~CNObserverDummy() {}

protected:
    CNObserverDummy() {}

public:
    virtual void update() {};
};

class CNObserverSpy;
typedef std::shared_ptr<CNObserverSpy> CNObserverSpyPtr;
class CNObserverSpy : public CNObserverDummy {
public:
    static CNObserverSpyPtr getNewInstance() {
        return CNObserverSpyPtr(new CNObserverSpy());
    }
    virtual ~CNObserverSpy() {}

protected:
    CNObserverSpy() {}

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

#endif //CROSSNATIVE_OBSERVER_TESTDOUBLES_H