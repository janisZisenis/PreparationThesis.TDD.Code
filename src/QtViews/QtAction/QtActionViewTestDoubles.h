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
    virtual bool getNewAccessibility() {
        return newAccessbility;
    }

private:
    bool newAccessbility = false;
};

#endif //QTVIEWS_QTACTIONVIEW_TESTDOUBLES_H