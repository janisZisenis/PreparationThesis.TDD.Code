#ifndef CROSSNATIVE_ACTIONACCESSIBILITY_MOCKS_H
#define CROSSNATIVE_ACTIONACCESSIBILITY_MOCKS_H

#include "CNActionAccessibility.h"

class CNActionAccessibilityDummy;
typedef std::shared_ptr<CNActionAccessibilityDummy> CNActionAccessibilityDummyPtr;
class CNActionAccessibilityDummy : public CNActionAccessibility {
public:
    static CNActionAccessibilityDummyPtr getNewInstance() {
        return CNActionAccessibilityDummyPtr(new CNActionAccessibilityDummy());
    }
    virtual ~CNActionAccessibilityDummy() {}
protected:
    CNActionAccessibilityDummy() {}

public:
    virtual bool isAccessible() override { return false; };
};

class CNActionAccessibilityStub;
typedef std::shared_ptr<CNActionAccessibilityStub> CNActionAccessibilityStubPtr;
class CNActionAccessibilityStub : public CNActionAccessibilityDummy {
public:
    static CNActionAccessibilityStubPtr getNewInstance() {
        return CNActionAccessibilityStubPtr(new CNActionAccessibilityStub());
    }
    virtual ~CNActionAccessibilityStub() {}
protected:
    CNActionAccessibilityStub() {}

public:
    virtual bool isAccessible() override { return accessibility; };
    virtual void setIsAccessible(bool accessibility) {
        this->accessibility = accessibility;
    }

private:
    bool accessibility;
};

#endif //CROSSNATIVE_ACTIONACCESSIBILITY_MOCKS_H