#ifndef CODEBASE_OBSERVER_H
#define CODEBASE_OBSERVER_H

#include <memory>

class CBObserver;
typedef std::shared_ptr<CBObserver> CBObserverPtr;

class CBObserver {
public:
    virtual ~CBObserver() {}

protected:
    CBObserver() {}

public:
    virtual void update() = 0;
};

#endif //CODEBASE_OBSERVER_H