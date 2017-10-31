#ifndef CROSSNATIVE_COMPONENTADDER_TESTDOUBLES_H
#define CROSSNATIVE_COMPONENTADDER_TESTDOUBLES_H

#include "CNComponentAdder.h"

class CNComponentAdderDummy;
typedef std::shared_ptr<CNComponentAdderDummy> CNComponentAdderDummyPtr;
class CNComponentAdderDummy : public CNComponentAdder {
public:
    static CNComponentAdderDummyPtr getNewInstance() {
        return CNComponentAdderDummyPtr(new CNComponentAdderDummy);
    }
    virtual ~CNComponentAdderDummy() {};
protected:
    CNComponentAdderDummy() {};

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override {}
    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override {}

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return nullptr; }
};

class CNComponentAdderStub;
typedef std::shared_ptr<CNComponentAdderStub> CNComponentAdderStubPtr;
class CNComponentAdderStub : public CNComponentAdderDummy {
public:
    static CNComponentAdderStubPtr getNewInstance() {
        return CNComponentAdderStubPtr(new CNComponentAdderStub());
    }
    virtual ~CNComponentAdderStub() {};
protected:
    CNComponentAdderStub() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return retrievedcomponent; }
    virtual void returnsOnRetrieve(std::shared_ptr<CNComponent> component) { retrievedcomponent = component; }

private:
    std::shared_ptr<CNComponent> retrievedcomponent;
};

class CNComponentAdderSpy;
typedef std::shared_ptr<CNComponentAdderSpy> CNComponentAdderSpyPtr;
class CNComponentAdderSpy : public CNComponentAdderStub {
public:
    static CNComponentAdderSpyPtr getNewInstance() {
        return CNComponentAdderSpyPtr(new CNComponentAdderSpy());
    }
    virtual ~CNComponentAdderSpy() {};
protected:
    CNComponentAdderSpy() {};

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
        return CNComponentAdderStub::retrieve(index);
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

#endif //CROSSNATIVE_COMPONENTADDER_TESTDOUBLES_H
