#ifndef QTVIEWS_QTACTIONVIEW_TESTDOUBLES_H
#define QTVIEWS_QTACTIONVIEW_TESTDOUBLES_H

#include "QtActionView.h"

class QtActionViewDummy;
typedef std::shared_ptr<QtActionViewDummy> QtActionViewDummyPtr;
class QtActionViewDummy : public QtActionView {
public:
    static QtActionViewDummyPtr getNewInstance() {
        return QtActionViewDummyPtr(new QtActionViewDummy());
    }
    virtual ~QtActionViewDummy() {}
protected:
    QtActionViewDummy() {}

public:
    virtual void setAccessibility(bool newAccessibility) override {}
    virtual void setState(CBActionStates newState) override {}
};

class QtActionViewSpy;
typedef std::shared_ptr<QtActionViewSpy> QtActionViewSpyPtr;
class QtActionViewSpy : public QtActionView {
public:
    static QtActionViewSpyPtr getNewInstance() {
        return QtActionViewSpyPtr(new QtActionViewSpy());
    }
    virtual ~QtActionViewSpy() {}
protected:
    QtActionViewSpy() {}

public:
    virtual void setAccessibility(bool newAccessibility) override {
        this->newAccessbility = newAccessibility;
    }
    virtual bool getNewAccessibility() {
        return newAccessbility;
    }

    virtual void setState(CBActionStates newState) override {
        this->newState = newState;
    }
    virtual CBActionStates getNewState() {
        return newState;
    }

private:
    bool newAccessbility = false;
    CBActionStates newState = OFF;
};

#endif //QTVIEWS_QTACTIONVIEW_TESTDOUBLES_H