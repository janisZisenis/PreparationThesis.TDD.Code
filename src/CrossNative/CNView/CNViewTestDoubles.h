#ifndef CROSSNATIVE_VIEW_TESTDOUBLES_H
#define CROSSNATIVE_VIEW_TESTDOUBLES_H

#include "CNView.h"

class CNViewDummy;
typedef std::shared_ptr<CNViewDummy> CNViewDummyPtr;
class CNViewDummy : public CNView {
public:
    static CNViewDummyPtr getNewInstance() {
        return CNViewDummyPtr(new CNViewDummy());
    }
    virtual ~CNViewDummy() {};
protected:
    CNViewDummy() {};

public:
    virtual void add(CNViewPtr view) override {};
    virtual void remove(CNViewPtr view) override {};
};

class CNViewStub;
typedef std::shared_ptr<CNViewStub> CNViewStubPtr;
class CNViewStub : public CNViewDummy {
public:
    static CNViewStubPtr getNewInstance() {
        return CNViewStubPtr(new CNViewStub());
    }
    virtual ~CNViewStub() {}
protected:
    CNViewStub() {}

public:
    virtual void setIsParentOf(bool isParent) {
        this->isParent = isParent;
    }
private:
    bool isParent = false;
};

class CNViewSpy;
typedef std::shared_ptr<CNViewSpy> CNViewSpyPtr;
class CNViewSpy : public CNViewStub {
public:
    static CNViewSpyPtr getNewInstance() {
        return CNViewSpyPtr(new CNViewSpy());
    }
    virtual ~CNViewSpy() {};
protected:
    CNViewSpy() {};

public:
    virtual void add(CNViewPtr view) override {
        added = view;
    };
    virtual CNViewPtr getAddedView() {
        return added;
    }

    virtual void remove(CNViewPtr view) override {
        removed = view;
    }
    virtual CNViewPtr getRemovedView() {
        return removed;
    }

private:
    CNViewPtr added;
    CNViewPtr removed;
};

#endif //CROSSNATIVE_VIEW_H