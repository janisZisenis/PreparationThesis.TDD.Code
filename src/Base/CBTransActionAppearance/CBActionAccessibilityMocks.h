#ifndef CODEBASE_ACTIONACCESSIBILITY_MOCKS_H
#define CODEBASE_ACTIONACCESSIBILITY_MOCKS_H

#include "CBActionAccessibility.h"

class CBActionAccessibilityDummy;
typedef std::shared_ptr<CBActionAccessibilityDummy> CBActionAccessibilityDummyPtr;
class CBActionAccessibilityDummy : public CBActionAccessibility {
public:
    static CBActionAccessibilityDummyPtr getNewInstance() {
        return CBActionAccessibilityDummyPtr(new CBActionAccessibilityDummy());
    }
    virtual ~CBActionAccessibilityDummy() {}
protected:
    CBActionAccessibilityDummy() {}

public:
    virtual bool isAccessible() override { return false; };
};

class CBActionAccessibilityStub;
typedef std::shared_ptr<CBActionAccessibilityStub> CBActionAccessibilityStubPtr;
class CBActionAccessibilityStub : public CBActionAccessibilityDummy {
public:
    static CBActionAccessibilityStubPtr getNewInstance() {
        return CBActionAccessibilityStubPtr(new CBActionAccessibilityStub());
    }
    virtual ~CBActionAccessibilityStub() {}
protected:
    CBActionAccessibilityStub() {}

public:
    virtual bool isAccessible() override { return accessibility; };
    virtual void setIsAccessible(bool accessibility) {
        this->accessibility = accessibility;
    }

private:
    bool accessibility;
};

#endif //CODEBASE_ACTIONACCESSIBILITY_MOCKS_H