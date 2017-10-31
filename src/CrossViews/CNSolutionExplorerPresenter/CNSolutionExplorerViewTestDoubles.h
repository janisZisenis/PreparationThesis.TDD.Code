#ifndef CROSSNATIVE_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H
#define CROSSNATIVE_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H

#include "CNSolutionExplorerView.h"

class CNSolutionExplorerViewDummy;
typedef std::shared_ptr<CNSolutionExplorerViewDummy> CNSolutionExplorerViewDummyPtr;
class CNSolutionExplorerViewDummy : public CNSolutionExplorerView {
public:
    static CNSolutionExplorerViewDummyPtr getNewInstance() {
        return CNSolutionExplorerViewDummyPtr(new CNSolutionExplorerViewDummy());
    }
    virtual ~CNSolutionExplorerViewDummy() {}
protected:
    CNSolutionExplorerViewDummy() {}

public:
    void accept(CNVisitorPtr visitor) override {}
    virtual void removeIndex(const CNHierarchyIndex& index) override {}
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) override {}
    virtual CNHierarchyIndex getSelectedIndex() override {
        return CNHierarchyIndex();
    };

    virtual void setListener(std::shared_ptr<CNSolutionExplorerListener> listener) override {}
};

class CNSolutionExplorerViewStub;
typedef std::shared_ptr<CNSolutionExplorerViewStub> CNSolutionExplorerViewStubPtr;
class CNSolutionExplorerViewStub : public CNSolutionExplorerViewDummy {
public:
    static CNSolutionExplorerViewStubPtr getNewInstance() {
        return CNSolutionExplorerViewStubPtr(new CNSolutionExplorerViewStub());
    }
    virtual ~CNSolutionExplorerViewStub() {}
protected:
    CNSolutionExplorerViewStub() {}

public:
    virtual void setSelectedIndex(const CNHierarchyIndex& selected) {
        this->selected = selected;
    }
    virtual CNHierarchyIndex getSelectedIndex() override {
        return selected;
    };
private:
    CNHierarchyIndex selected;
};

class CNSolutionExplorerViewSpy;
typedef std::shared_ptr<CNSolutionExplorerViewSpy> CNSolutionExplorerViewSpyPtr;
class CNSolutionExplorerViewSpy : public CNSolutionExplorerViewStub {
public:
    static CNSolutionExplorerViewSpyPtr getNewInstance() {
        return CNSolutionExplorerViewSpyPtr(new CNSolutionExplorerViewSpy());
    }
    virtual ~CNSolutionExplorerViewSpy() {}
protected:
    CNSolutionExplorerViewSpy() {}

public:
    virtual void accept(CNVisitorPtr visitor) override {
        accepted = visitor;
    }
    virtual CNVisitorPtr getAccepted() {
        return accepted;
    }

    virtual void removeIndex(const CNHierarchyIndex& index) override {
        removed = index;
;    }
    virtual const CNHierarchyIndex& getRemoved() {
        return removed;
    }

private:
    CNHierarchyIndex removed;
    CNVisitorPtr accepted;
};

#endif //CROSSNATIVE_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H
