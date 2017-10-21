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
    virtual  ~CNComponentDummy() {};

protected:
    CNComponentDummy() {};

public:
    virtual bool isParentOf(CNComponentPtr component) override {
        return false;
    }
    virtual int getChildCount() override {
        return 0;
    }
    virtual CNComponentPtr getChild(int childPosition) override {
        return 0;
    }

    virtual void add(CNComponentPtr component) override {}
    virtual void remove(CNComponentPtr component) override {}
    virtual void insert(CNComponentPtr component, int childPos) override {}
    virtual void remove(int childPos) override {}

    virtual void accept(CNVisitorPtr visitor) override {}
};

class CNComponentStub;
typedef std::shared_ptr<CNComponentStub> CNComponentStubPtr;
class CNComponentStub : public CNComponentDummy {
public:
    static CNComponentStubPtr getNewInstance() {
        return CNComponentStubPtr(new CNComponentStub());
    }
    virtual  ~CNComponentStub() {};

protected:
    CNComponentStub() {};

public:
    virtual void setIsParentOf(bool isParent) {
        this->isParent = isParent;
    }
    virtual bool isParentOf(CNComponentPtr component) override {
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
    virtual  ~CNComponentSpy() {};

protected:
    CNComponentSpy() {};

public:
    virtual void add(CNComponentPtr component) override {
        added = component;
    }
    virtual CNComponentPtr getAdded() {
        return added;
    }

    virtual void remove(CNComponentPtr component) override {
        removed = component;
    }
    virtual CNComponentPtr getRemoved() {
        return removed;
    }

private:
    CNComponentPtr added;
    CNComponentPtr removed;
};

#endif //CROSSNATIVE_COMPONENT_TESTDOUBLES_H