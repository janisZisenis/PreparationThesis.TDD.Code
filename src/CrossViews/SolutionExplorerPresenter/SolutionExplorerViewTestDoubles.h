#ifndef CROSSVIEWS_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H
#define CROSSVIEWS_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H

#include "SolutionExplorerView.h"

class SolutionExplorerViewDummy;
typedef std::shared_ptr<SolutionExplorerViewDummy> SolutionExplorerViewDummyPtr;
class SolutionExplorerViewDummy : public SolutionExplorerView {
public:
    static SolutionExplorerViewDummyPtr getNewInstance() {
        return SolutionExplorerViewDummyPtr(new SolutionExplorerViewDummy());
    }
    virtual ~SolutionExplorerViewDummy() {}
protected:
    SolutionExplorerViewDummy() {}

public:
    void accept(CNVisitorPtr visitor) override {}
    virtual void removeIndex(const CNHierarchyIndex& index) override {}
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) override {}
    virtual CNHierarchyIndex getSelectedIndex() override {
        return CNHierarchyIndex();
    };

    virtual void setListener(std::shared_ptr<SolutionExplorerListener> listener) override {}
};

class SolutionExplorerViewStub;
typedef std::shared_ptr<SolutionExplorerViewStub> SolutionExplorerViewStubPtr;
class SolutionExplorerViewStub : public SolutionExplorerViewDummy {
public:
    static SolutionExplorerViewStubPtr getNewInstance() {
        return SolutionExplorerViewStubPtr(new SolutionExplorerViewStub());
    }
    virtual ~SolutionExplorerViewStub() {}
protected:
    SolutionExplorerViewStub() {}

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

class SolutionExplorerViewSpy;
typedef std::shared_ptr<SolutionExplorerViewSpy> SolutionExplorerViewSpyPtr;
class SolutionExplorerViewSpy : public SolutionExplorerViewStub {
public:
    static SolutionExplorerViewSpyPtr getNewInstance() {
        return SolutionExplorerViewSpyPtr(new SolutionExplorerViewSpy());
    }
    virtual ~SolutionExplorerViewSpy() {}
protected:
    SolutionExplorerViewSpy() {}

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

#endif //CROSSVIEWS_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H
