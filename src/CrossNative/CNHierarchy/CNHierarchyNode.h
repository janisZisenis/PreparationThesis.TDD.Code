#ifndef CROSSNATIVE_HIERARCHYNODE_H
#define CROSSNATIVE_HIERARCHYNODE_H

#include <memory>

class CNComponent;

class CNHierarchyNode;
typedef std::shared_ptr<CNHierarchyNode> CNHierarchyNodePtr;
class CNHierarchyNode {
public:
    static CNHierarchyNodePtr getNewInstance() {
        return CNHierarchyNodePtr(new CNHierarchyNode());
    }
    virtual  ~CNHierarchyNode() {}

protected:
    CNHierarchyNode();

public:
    virtual void add(std::shared_ptr<CNComponent> component) {}
    virtual void remove(std::shared_ptr<CNComponent> component) {}
    virtual void insert(std::shared_ptr<CNComponent> component, int childPos) {}
};

#endif //CROSSNATIVE_HIERARCHYNODE_H