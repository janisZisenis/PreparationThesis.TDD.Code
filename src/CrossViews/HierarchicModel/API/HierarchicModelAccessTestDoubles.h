#ifndef CROSSVIEWS_HIERARCHICMODELACCESS_TESTDOUBLES_H
#define CROSSVIEWS_HIERARCHICMODELACCESS_TESTDOUBLES_H

#include "HierarchicModelAccess.h"
#include <vector>

class HierarchicModelAccessDummy;
typedef std::shared_ptr<HierarchicModelAccessDummy> HierarchicModelAccessDummyPtr;
class HierarchicModelAccessDummy : public HierarchicModelAccess {
public:
    static HierarchicModelAccessDummyPtr getNewInstance() {
        return HierarchicModelAccessDummyPtr(new HierarchicModelAccessDummy);
    }
    virtual ~HierarchicModelAccessDummy() {};
protected:
    HierarchicModelAccessDummy() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return nullptr; }
};

class HierarchicModelAccessStub;
typedef std::shared_ptr<HierarchicModelAccessStub> HierarchicModelAccessStubPtr;
class HierarchicModelAccessStub : public HierarchicModelAccessDummy {
public:
    static HierarchicModelAccessStubPtr getNewInstance() {
        return HierarchicModelAccessStubPtr(new HierarchicModelAccessStub());
    }
    virtual ~HierarchicModelAccessStub() {};
protected:
    HierarchicModelAccessStub() {};
};

#endif //CROSSVIEWS_HIERARCHICMODELACCESS_TESTDOUBLES_H
