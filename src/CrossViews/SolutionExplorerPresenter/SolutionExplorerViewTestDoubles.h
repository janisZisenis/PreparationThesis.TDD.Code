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
    virtual void removeIndex(const HierarchyIndex& index) override {}
    virtual void insertItem(CNVisitablePtr visitable, const HierarchyIndex& parent, int childPos) override {}
};

class SolutionExplorerViewSpy;
typedef std::shared_ptr<SolutionExplorerViewSpy> SolutionExplorerViewSpyPtr;
class SolutionExplorerViewSpy : public SolutionExplorerViewDummy {
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

    virtual void removeIndex(const HierarchyIndex& index) override {
        removed = index;
;    }
    virtual const HierarchyIndex& getRemoved() {
        return removed;
    }

private:
    HierarchyIndex removed;
    CNVisitorPtr accepted;
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERVIEW_TESTDOUBLES_H
