#ifndef CROSSVIEWS_INSERTINGHIERARCHICMODEL_TESTDOUBLES_H
#define CROSSVIEWS_INSERTINGHIERARCHICMODEL_TESTDOUBLES_H

#include "InsertingHierarchicModel.h"

class InsertingHierarchicModelDummy;
typedef std::shared_ptr<InsertingHierarchicModelDummy> InsertingHierarchicModelDummyPtr;
class InsertingHierarchicModelDummy : public InsertingHierarchicModel {
public:
    static InsertingHierarchicModelDummyPtr getNewInstance() {
        return InsertingHierarchicModelDummyPtr(new InsertingHierarchicModelDummy);
    }
    virtual ~InsertingHierarchicModelDummy() {};
protected:
    InsertingHierarchicModelDummy() {};

public:
    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent, int childPos) override {}
    virtual void remove(const CNHierarchyIndex& parent, int childPos) override {}

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) override { return nullptr; };
};

class InsertingHierarchicModelStub;
typedef std::shared_ptr<InsertingHierarchicModelStub> InsertingHierarchicModelStubPtr;
class InsertingHierarchicModelStub : public InsertingHierarchicModelDummy {
public:
    static InsertingHierarchicModelStubPtr getNewInstance() {
        return InsertingHierarchicModelStubPtr(new InsertingHierarchicModelStub);
    }
    virtual ~InsertingHierarchicModelStub() {};
protected:
    InsertingHierarchicModelStub() {};
};

class InsertingHierarchicModelSpy;
typedef std::shared_ptr<InsertingHierarchicModelSpy> InsertingHierarchicModelSpyPtr;
class InsertingHierarchicModelSpy : public InsertingHierarchicModelStub {
public:
    static InsertingHierarchicModelSpyPtr getNewInstance() {
        return InsertingHierarchicModelSpyPtr(new InsertingHierarchicModelSpy);
    }
    virtual ~InsertingHierarchicModelSpy() {};
protected:
    InsertingHierarchicModelSpy() {};

public:
    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent, int childPos) override {
        insertedChildPos = childPos;
        insertingIndex = parent;
        insertedcomponent = component;
    };
    virtual int getInsertedChildPos() {
        return insertedChildPos;
    }
    virtual CNHierarchyIndex getInsertingIndex() {
        return insertingIndex;
    }

    virtual void remove(const CNHierarchyIndex& parent, int childPos) override {
        removingIndex = parent;
        removedChildPos = childPos;
    }

    virtual int getRemovedChildPos() {
        return removedChildPos;
    }
    virtual CNHierarchyIndex getRemovingIndex() {
        return removingIndex;
    }

    virtual std::shared_ptr<CNComponent> getInsertedcomponent() {
        return insertedcomponent;
    }
private:
    std::shared_ptr<CNComponent> insertedcomponent;
    int insertedChildPos;
    CNHierarchyIndex insertingIndex;
    int removedChildPos;
    CNHierarchyIndex removingIndex;

};

#endif //CROSSVIEWS_INSERTINGHIERARCHICMODEL_TESTDOUBLES_H
