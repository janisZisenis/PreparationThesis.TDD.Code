#ifndef CROSSNATIVE_HIERARCHYNODE_TESTDOUBLES_H
#define CROSSNATIVE_HIERARCHYNODE_TESTDOUBLES_H

#include "CNHierarchyNode.h"

class CNHierarchyNodeDummy;
typedef std::shared_ptr<CNHierarchyNodeDummy> CNHierarchyNodeDummyPtr;
class CNHierarchyNodeDummy : public CNHierarchyNode {
public:
    static CNHierarchyNodeDummyPtr getNewInstance() {
        return CNHierarchyNodeDummyPtr(new CNHierarchyNodeDummy());
    }
    virtual  ~CNHierarchyNodeDummy() {};

protected:
    CNHierarchyNodeDummy() {};

public:
    virtual bool isParentOf(CNHierarchyNodePtr node) override {
        return false;
    }
    virtual int getChildCount() override {
        return 0;
    }
    virtual CNHierarchyNodePtr getChild(int childPosition) override {
        return 0;
    }

    virtual void add(CNHierarchyNodePtr node) override {}
    virtual void remove(CNHierarchyNodePtr node) override {}
    virtual void insert(CNHierarchyNodePtr node, int childPos) override {}
};

class CNHierarchyNodeSpy;
typedef std::shared_ptr<CNHierarchyNodeSpy> CNHierarchyNodeSpyPtr;
class CNHierarchyNodeSpy : public CNHierarchyNodeDummy {
public:
    static CNHierarchyNodeSpyPtr getNewInstance() {
        return CNHierarchyNodeSpyPtr(new CNHierarchyNodeSpy());
    }
    virtual  ~CNHierarchyNodeSpy() {};

protected:
    CNHierarchyNodeSpy() {};

public:
    virtual void add(CNHierarchyNodePtr node) override {
        added = node;
    }
    virtual CNHierarchyNodePtr getAdded() {
        return added;
    }

private:
    CNHierarchyNodePtr added;
};

#endif //CROSSNATIVE_HIERARCHYNODE_TESTDOUBLES_H