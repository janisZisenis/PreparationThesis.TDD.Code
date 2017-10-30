#ifndef CROSSVIEWS_COMPONENTLOADER_TESTDOUBLES_H
#define CROSSVIEWS_COMPONENTLOADER_TESTDOUBLES_H

#include "ComponentLoader.h"

class ComponentLoaderDummy;
typedef std::shared_ptr<ComponentLoaderDummy> ComponentLoaderDummyPtr;
class ComponentLoaderDummy : public ComponentLoader {
public:
    static ComponentLoaderDummyPtr getNewInstance() {
        return ComponentLoaderDummyPtr(new ComponentLoaderDummy());
    }
    virtual ~ComponentLoaderDummy() {}
protected:
    ComponentLoaderDummy() {}

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) {}
};

class ComponentLoaderSpy;
typedef std::shared_ptr<ComponentLoaderSpy> ComponentLoaderSpyPtr;
class ComponentLoaderSpy : public ComponentLoaderDummy {
public:
    static ComponentLoaderSpyPtr getNewInstance() {
        return ComponentLoaderSpyPtr(new ComponentLoaderSpy());
    }
    virtual ~ComponentLoaderSpy() {}
protected:
    ComponentLoaderSpy() {}

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) {
        this->component = component;
        this->matcher = matcher;
        loadedCalled = true;
    }

    virtual std::shared_ptr<CNComponent> getLoadedComponent() {
        return component;
    }
    virtual std::shared_ptr<CNMatcher> getLoadedMatcher() {
        return matcher;
    }
    virtual bool loadedWasCalled() {
        return loadedCalled;
    }
private:
    bool loadedCalled = false;
    std::shared_ptr<CNComponent> component;
    std::shared_ptr<CNMatcher> matcher;
};


#endif //CROSSVIEWS_COMPONENTLOADER_TESTDOUBLES_H