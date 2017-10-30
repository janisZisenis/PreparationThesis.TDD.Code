#ifndef CROSSNATIVE_OBSERVER_H
#define CROSSNATIVE_OBSERVER_H

#include <memory>

class CNObserver;
typedef std::shared_ptr<CNObserver> CNObserverPtr;

class CNObserver {
public:
    virtual ~CNObserver() {}

protected:
    CNObserver() {}

public:
    virtual void update() = 0;
};

#endif //CROSSNATIVE_OBSERVER_H