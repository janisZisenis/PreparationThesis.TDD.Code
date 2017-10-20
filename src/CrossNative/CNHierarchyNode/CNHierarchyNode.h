#ifndef CROSSNATIVE_HIERARCHYNODE_H
#define CROSSNATIVE_HIERARCHYNODE_H

#include <memory>
#include "CrossNative/CNComponent/CNChildNotFoundException.h"
#include "CNInvalidInsertingPositionException.h"

class CNHierarchyNode;
typedef std::shared_ptr<CNHierarchyNode> CNHierarchyNodePtr;
class CNHierarchyNode {
public:
    virtual  ~CNHierarchyNode() {};

protected:
    CNHierarchyNode() {};

public:
    virtual bool isParentOf(CNHierarchyNodePtr node) = 0;

    virtual void add(CNHierarchyNodePtr node) = 0;
    virtual void remove(CNHierarchyNodePtr node) = 0;
    virtual void insert(CNHierarchyNodePtr node, int childPos) = 0;
};

#endif //CROSSNATIVE_HIERARCHYNODE_H