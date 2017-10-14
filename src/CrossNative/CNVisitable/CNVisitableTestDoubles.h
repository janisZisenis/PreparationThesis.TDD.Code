#ifndef CROSSNATIVE_VISITABLE_TESTDOUBLES_H
#define CROSSNATIVE_VISITABLE_TESTDOUBLES_H

#include "CNVisitable.h"

class CNVisitableDummy;
typedef std::shared_ptr<CNVisitableDummy> CNVisitableDummyPtr;
class CNVisitableDummy : public CNVisitable {
public:
    static CNVisitableDummyPtr getNewInstance() {
        return CNVisitableDummyPtr(new CNVisitableDummy());
    };
    virtual ~CNVisitableDummy() {}

protected:
    CNVisitableDummy() {}

public:
    virtual void accept(CNVisitorPtr visitor) override {};
};

class CNVisitableSpy;
typedef std::shared_ptr<CNVisitableSpy> CNVisitableSpyPtr;
class CNVisitableSpy : public CNVisitableDummy {
public:
    static CNVisitableSpyPtr getNewInstance() {
        return CNVisitableSpyPtr(new CNVisitableSpy());
    };
    virtual ~CNVisitableSpy() {}

protected:
    CNVisitableSpy() {}

public:
    virtual void accept(CNVisitorPtr visitor) override {
        accepted = visitor;
    };

    virtual CNVisitorPtr getAccepted() {
        return accepted;
    }
private:
    CNVisitorPtr accepted;
};

#endif //CROSSNATIVE_VISITABLE_TESTDOUBLES_H