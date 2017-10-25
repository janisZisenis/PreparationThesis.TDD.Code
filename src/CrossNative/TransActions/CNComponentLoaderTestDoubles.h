#ifndef CROSSNATIVE_COMPONENTLOADER_TESTDOUBLES_H
#define CROSSNATIVE_COMPONENTLOADER_TESTDOUBLES_H

#include "CNComponentLoader.h"

class CNComponentLoaderDummy;
typedef std::shared_ptr<CNComponentLoaderDummy> CNComponentLoaderDummyPtr;
class CNComponentLoaderDummy : public CNComponentLoader {
public:
    static CNComponentLoaderDummyPtr getNewInstance() {
        return CNComponentLoaderDummyPtr(new CNComponentLoaderDummy());
    }
    virtual ~CNComponentLoaderDummy() {}
protected:
    CNComponentLoaderDummy() {}

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) {}
};

class CNComponentLoaderSpy;
typedef std::shared_ptr<CNComponentLoaderSpy> CNComponentLoaderSpyPtr;
class CNComponentLoaderSpy : public CNComponentLoaderDummy {
public:
    static CNComponentLoaderSpyPtr getNewInstance() {
        return CNComponentLoaderSpyPtr(new CNComponentLoaderSpy());
    }
    virtual ~CNComponentLoaderSpy() {}
protected:
    CNComponentLoaderSpy() {}

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) {
        this->component = component;
        this->matcher = matcher;
    }

    virtual std::shared_ptr<CNComponent> getLoadedComponent() {
        return component;
    }
    virtual std::shared_ptr<CNMatcher> getLoadedMatcher() {
        return matcher;
    }
private:
    std::shared_ptr<CNComponent> component;
    std::shared_ptr<CNMatcher> matcher;
};


#endif //CROSSNATIVE_COMPONENTLOADER_TESTDOUBLES_H