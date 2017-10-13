#ifndef CROSSNATIVE_COMPONENT_TESTDOUBLES_H
#define CROSSNATIVE_COMPONENT_TESTDOUBLES_H

#include "CNComponent.h"

class CNComponentDummy;
typedef std::shared_ptr<CNComponentDummy> CNComponentDummyPtr;
class CNComponentDummy : public CNComponent {
public:
    static CNComponentDummyPtr getNewInstance() {
        return CNComponentDummyPtr(new CNComponentDummy());
    }
    virtual ~CNComponentDummy() {};
protected:
    CNComponentDummy() {};

public:
    virtual void add(CNComponentPtr view) override {};
    virtual void remove(CNComponentPtr view) override {};
    virtual bool isParentOf(CNComponentPtr view) override {
        return false;
    }
};

class CNComponentStub;
typedef std::shared_ptr<CNComponentStub> CNComponentStubPtr;
class CNComponentStub : public CNComponentDummy {
public:
    static CNComponentStubPtr getNewInstance() {
        return CNComponentStubPtr(new CNComponentStub());
    }
    virtual ~CNComponentStub() {}
protected:
    CNComponentStub() {}

public:
    virtual void setIsParentOf(bool isParent) {
        this->isParent = isParent;
    }
    virtual bool isParentOf(CNComponentPtr view) override {
        return isParent;
    }
private:
    bool isParent = false;
};

class CNComponentSpy;
typedef std::shared_ptr<CNComponentSpy> CNComponentSpyPtr;
class CNComponentSpy : public CNComponentStub {
public:
    static CNComponentSpyPtr getNewInstance() {
        return CNComponentSpyPtr(new CNComponentSpy());
    }
    virtual ~CNComponentSpy() {};
protected:
    CNComponentSpy() {};

public:
    virtual void add(CNComponentPtr view) override {
        added = view;
    };
    virtual CNComponentPtr getAdded() {
        return added;
    }

    virtual void remove(CNComponentPtr view) override {
        removed = view;
    }
    virtual CNComponentPtr getRemoved() {
        return removed;
    }

private:
    CNComponentPtr added;
    CNComponentPtr removed;
};

#endif //CROSSNATIVE_COMPONENT_TESTDOUBLES_H