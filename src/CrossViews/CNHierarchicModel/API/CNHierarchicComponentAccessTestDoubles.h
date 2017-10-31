#ifndef CROSSNATIVE_HIERARCHICMODELACCESS_TESTDOUBLES_H
#define CROSSNATIVE_HIERARCHICMODELACCESS_TESTDOUBLES_H

#include "CNHierarchicComponentAccess.h"
#include <vector>

class CNHierarchicComponentAccessDummy;
typedef std::shared_ptr<CNHierarchicComponentAccessDummy> CNHierarchicComponentAccessDummyPtr;
class CNHierarchicComponentAccessDummy : public CNHierarchicComponentAccess {
public:
    static CNHierarchicComponentAccessDummyPtr getNewInstance() {
        return CNHierarchicComponentAccessDummyPtr(new CNHierarchicComponentAccessDummy);
    }
    virtual ~CNHierarchicComponentAccessDummy() {};
protected:
    CNHierarchicComponentAccessDummy() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return nullptr; }

    virtual void addListener(std::shared_ptr<CNHierarchicModelListener> observer) override {}
    virtual void removeListener(std::shared_ptr<CNHierarchicModelListener> observer) override {}
};

class CNHierarchicComponentAccessStub;
typedef std::shared_ptr<CNHierarchicComponentAccessStub> CNHierarchicComponentAccessStubPtr;
class CNHierarchicComponentAccessStub : public CNHierarchicComponentAccessDummy {
public:
    static CNHierarchicComponentAccessStubPtr getNewInstance() {
        return CNHierarchicComponentAccessStubPtr(new CNHierarchicComponentAccessStub());
    }
    virtual ~CNHierarchicComponentAccessStub() {};
protected:
    CNHierarchicComponentAccessStub() {};

public:
    virtual void setRetrieved(std::shared_ptr<CNComponent> component) {
        retrieved = component;
    }
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) {
        return retrieved;
    }
private:
    std::shared_ptr<CNComponent> retrieved;
};

class CNHierarchicComponentAccessSpy;
typedef std::shared_ptr<CNHierarchicComponentAccessSpy> CNHierarchicComponentAccessSpyPtr;
class CNHierarchicComponentAccessSpy : public CNHierarchicComponentAccessStub {
public:
    static CNHierarchicComponentAccessSpyPtr getNewInstance() {
        return CNHierarchicComponentAccessSpyPtr(new CNHierarchicComponentAccessSpy());
    }
    virtual ~CNHierarchicComponentAccessSpy() {};
protected:
    CNHierarchicComponentAccessSpy() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) {
        retrievedIndex = index;
        return CNHierarchicComponentAccessStub::retrieve(index);
    }
    virtual CNHierarchyIndex getRetrievedIndex() {
        return retrievedIndex;
    }
private:
    CNHierarchyIndex retrievedIndex;
};

#endif //CROSSNATIVE_HIERARCHICMODELACCESS_TESTDOUBLES_H
