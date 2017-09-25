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
    virtual CNViewPtr getChild(int position) override {
        return nullptr;
    };
    virtual int getChildCount() override {
        return 0;
    };
};

class CNViewSpy;
typedef std::shared_ptr<CNViewSpy> CNViewSpyPtr;
class CNViewSpy : public CNViewDummy {
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

private:
    CNViewPtr added;
};

#endif //CROSSNATIVE_VIEW_H