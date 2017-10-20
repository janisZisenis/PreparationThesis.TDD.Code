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
    };

    virtual void add(std::shared_ptr<CNHierarchyNode> node) override {}
    virtual void remove(std::shared_ptr<CNHierarchyNode> node) override {}
    virtual void insert(std::shared_ptr<CNHierarchyNode> node, int childPos) override {}
};

#endif //CROSSNATIVE_HIERARCHYNODE_TESTDOUBLES_H