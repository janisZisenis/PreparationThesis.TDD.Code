#ifndef CROSSVIEWS_HIERARCHICMODELACCESS_TESTDOUBLES_H
#define CROSSVIEWS_HIERARCHICMODELACCESS_TESTDOUBLES_H

#include "HierarchicModelAccess.h"

class HierarchicModelAccessDummy;
typedef std::shared_ptr<HierarchicModelAccessDummy> HierarchicModelAccessDummyPtr;
class HierarchicModelAccessDummy : public HierarchicModelAccess {
public:
    static HierarchicModelAccessDummyPtr getNewInstance() {
        return HierarchicModelAccessDummyPtr(new HierarchicModelAccessDummy());
    }
    virtual ~HierarchicModelAccessDummy() {};
protected:
    HierarchicModelAccessDummy() {};

public:
    virtual std::shared_ptr<CNVisitable> retrieve(const HierarchyIndex& index) {
        return nullptr;
    }
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

public:
    virtual void setRetrieved(std::shared_ptr<CNVisitable> retrieved) {
        this->retrieved = retrieved;
    }
    virtual std::shared_ptr<CNVisitable> retrieve(const HierarchyIndex& index) {
        return retrieved;
    }

private:
    std::shared_ptr<CNVisitable> retrieved;
};

class HierarchicModelAccessSpy;
typedef std::shared_ptr<HierarchicModelAccessSpy> HierarchicModelAccessSpyPtr;
class HierarchicModelAccessSpy : public HierarchicModelAccessStub {
public:
    static HierarchicModelAccessSpyPtr getNewInstance() {
        return HierarchicModelAccessSpyPtr(new HierarchicModelAccessSpy());
    }
    virtual ~HierarchicModelAccessSpy() {};
protected:
    HierarchicModelAccessSpy() {};

public:
    virtual std::shared_ptr<CNVisitable> retrieve(const HierarchyIndex& index) {
        retrievedIndex = index;
        return HierarchicModelAccessStub::retrieve(index);
    }

    virtual HierarchyIndex getRetrievedIndex() {
        return retrievedIndex;
    }
private:
    HierarchyIndex retrievedIndex;
};

#endif //CROSSVIEWS_HIERARCHICMODELACCESS_TESTDOUBLES_H
