#ifndef CROSSNATIVE_MENUVIEW_TESTDOUBLES_H
#define CROSSNATIVE_MENUVIEW_TESTDOUBLES_H

#include "CNMenuView.h"

class CNMenuViewDummy;
typedef std::shared_ptr<CNMenuViewDummy> CNMenuViewDummyPtr;
class CNMenuViewDummy : public CNMenuView {
public:
    static CNMenuViewDummyPtr getNewInstance() {
        return CNMenuViewDummyPtr(new CNMenuViewDummy());
    }
    virtual ~CNMenuViewDummy() {}
protected:
    CNMenuViewDummy() {}

public:
    virtual void accept(CNVisitorPtr accept) override {}
};

class CNMenuViewSpy;
typedef std::shared_ptr<CNMenuViewSpy> CNMenuViewSpyPtr;
class CNMenuViewSpy : public CNMenuViewDummy {
public:
    static CNMenuViewSpyPtr getNewInstance() {
        return CNMenuViewSpyPtr(new CNMenuViewSpy());
    }
    virtual ~CNMenuViewSpy() {}
protected:
    CNMenuViewSpy() {}

public:
    virtual void accept(CNVisitorPtr visitor) override {
        accepted = visitor;
    }
    virtual CNVisitorPtr getAccepted() {
        return accepted;
    }

private:
    CNVisitorPtr accepted;
};

#endif //CROSSNATIVE_MENUVIEW_TESTDOUBLES_H
