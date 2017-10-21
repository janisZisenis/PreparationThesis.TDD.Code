#ifndef CROSSVIEWS_ADDINGHIERARCHICMODEL_TESTDOUBLES_H
#define CROSSVIEWS_ADDINGHIERARCHICMODEL_TESTDOUBLES_H

#include "AddingHierarchicModel.h"

class AddingHierarchicModelDummy;
typedef std::shared_ptr<AddingHierarchicModelDummy> AddingHierarchicModelDummyPtr;
class AddingHierarchicModelDummy : public AddingHierarchicModel {
public:
    static AddingHierarchicModelDummyPtr getNewInstance() {
        return AddingHierarchicModelDummyPtr(new AddingHierarchicModelDummy);
    }
    virtual ~AddingHierarchicModelDummy() {};
protected:
    AddingHierarchicModelDummy() {};

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override {}
    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override {}

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return nullptr; }
};

class AddingHierarchicModelStub;
typedef std::shared_ptr<AddingHierarchicModelStub> AddingHierarchicModelStubPtr;
class AddingHierarchicModelStub : public AddingHierarchicModelDummy {
public:
    static AddingHierarchicModelStubPtr getNewInstance() {
        return AddingHierarchicModelStubPtr(new AddingHierarchicModelStub());
    }
    virtual ~AddingHierarchicModelStub() {};
protected:
    AddingHierarchicModelStub() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return retrievedcomponent; }
    virtual void returnsOnRetrieve(std::shared_ptr<CNComponent> component) { retrievedcomponent = component; }

private:
    std::shared_ptr<CNComponent> retrievedcomponent;
};

class AddingHierarchicModelSpy;
typedef std::shared_ptr<AddingHierarchicModelSpy> AddingHierarchicModelSpyPtr;
class AddingHierarchicModelSpy : public AddingHierarchicModelStub {
public:
    static AddingHierarchicModelSpyPtr getNewInstance() {
        return AddingHierarchicModelSpyPtr(new AddingHierarchicModelSpy());
    }
    virtual ~AddingHierarchicModelSpy() {};
protected:
    AddingHierarchicModelSpy() {};

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override {
        addedcomponent = component;
        addingIndex = parent;
    }
    virtual std::shared_ptr<CNComponent> getAdded() {
        return addedcomponent;
    }
    virtual CNHierarchyIndex getAddedIndex() {
        return addingIndex;
    }

    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override {
        removedcomponent = component;
        removingIndex = parent;
    }
    virtual std::shared_ptr<CNComponent> getRemoved() {
        return removedcomponent;
    }
    virtual CNHierarchyIndex getRemovedIndex() {
        return removingIndex;
    }

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override {
        retrievedIndex = index;
        return AddingHierarchicModelStub::retrieve(index);
    }

    virtual CNHierarchyIndex getRetrievedIndex() {
        return retrievedIndex;
    }
private:
    std::shared_ptr<CNComponent> addedcomponent;
    CNHierarchyIndex addingIndex;
    std::shared_ptr<CNComponent> removedcomponent;
    CNHierarchyIndex removingIndex;
    CNHierarchyIndex retrievedIndex;
};

#endif //CROSSVIEWS_ADDINGHIERARCHICMODEL_TESTDOUBLES_H
