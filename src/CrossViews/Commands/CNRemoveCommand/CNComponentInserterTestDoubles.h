#ifndef CROSSNATIVE_COMPONENTINSERTER_TESTDOUBLES_H
#define CROSSNATIVE_COMPONENTINSERTER_TESTDOUBLES_H

#include "CNComponentInserter.h"

class CNComponentInserterDummy;
typedef std::shared_ptr<CNComponentInserterDummy> CNComponentInserterDummyPtr;
class CNComponentInserterDummy : public CNComponentInserter {
public:
    static CNComponentInserterDummyPtr getNewInstance() {
        return CNComponentInserterDummyPtr(new CNComponentInserterDummy);
    }
    virtual ~CNComponentInserterDummy() {};
protected:
    CNComponentInserterDummy() {};

public:
    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent, int childPos) override {}
    virtual void remove(const CNHierarchyIndex& parent, int childPos) override {}

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return nullptr; };
};

class CNComponentInserterStub;
typedef std::shared_ptr<CNComponentInserterStub> CNComponentInserterStubPtr;
class CNComponentInserterStub : public CNComponentInserterDummy {
public:
    static CNComponentInserterStubPtr getNewInstance() {
        return CNComponentInserterStubPtr(new CNComponentInserterStub);
    }
    virtual ~CNComponentInserterStub() {};
protected:
    CNComponentInserterStub() {};
};

class CNComponentInserterSpy;
typedef std::shared_ptr<CNComponentInserterSpy> CNComponentInserterSpyPtr;
class CNComponentInserterSpy : public CNComponentInserterStub {
public:
    static CNComponentInserterSpyPtr getNewInstance() {
        return CNComponentInserterSpyPtr(new CNComponentInserterSpy);
    }
    virtual ~CNComponentInserterSpy() {};
protected:
    CNComponentInserterSpy() {};

public:
    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent, int childPos) override {
        insertedChildPos = childPos;
        insertingIndex = parent;
        insertedcomponent = component;
    };
    virtual int getInsertedChildPos() {
        return insertedChildPos;
    }
    virtual CNHierarchyIndex getInsertedIndex() {
        return insertingIndex;
    }

    virtual void remove(const CNHierarchyIndex& parent, int childPos) override {
        removingIndex = parent;
        removedChildPos = childPos;
    }

    virtual int getRemovedChildPos() {
        return removedChildPos;
    }
    virtual CNHierarchyIndex getRemovedIndex() {
        return removingIndex;
    }

    virtual std::shared_ptr<CNComponent> getInserted() {
        return insertedcomponent;
    }
private:
    std::shared_ptr<CNComponent> insertedcomponent;
    int insertedChildPos;
    CNHierarchyIndex insertingIndex;
    int removedChildPos;
    CNHierarchyIndex removingIndex;

};

#endif //CROSSNATIVE_COMPONENTINSERTER_TESTDOUBLES_H
