#ifndef CROSSNATIVE_TRANSACTIONACCESSIBILITY_TESTDOUBLES_H
#define CROSSNATIVE_TRANSACTIONACCESSIBILITY_TESTDOUBLES_H

#include "CNTransActionAccessibility.h"

class CNTransActionAccessibilityDummy;
typedef std::shared_ptr<CNTransActionAccessibilityDummy> CNTransActionAccessibilityDummyPtr;
class CNTransActionAccessibilityDummy : public CNTransActionAccessibility {
public:
    static CNTransActionAccessibilityDummyPtr getNewInstance() {
        return CNTransActionAccessibilityDummyPtr(new CNTransActionAccessibilityDummy());
    }
    virtual ~CNTransActionAccessibilityDummy() {}
protected:
    CNTransActionAccessibilityDummy() {}

public:
    virtual bool isAccessible() override { return false; };
};

class CNTransActionAccessibilityStub;
typedef std::shared_ptr<CNTransActionAccessibilityStub> CNTransActionAccessibilityStubPtr;
class CNTransActionAccessibilityStub : public CNTransActionAccessibilityDummy {
public:
    static CNTransActionAccessibilityStubPtr getNewInstance() {
        return CNTransActionAccessibilityStubPtr(new CNTransActionAccessibilityStub());
    }
    virtual ~CNTransActionAccessibilityStub() {}
protected:
    CNTransActionAccessibilityStub() {}

public:
    virtual bool isAccessible() override { return accessibility; };
    virtual void setIsAccessible(bool accessibility) {
        this->accessibility = accessibility;
    }

private:
    bool accessibility;
};

#endif //CROSSNATIVE_TRANSACTIONACCESSIBILITY_TESTDOUBLES_H