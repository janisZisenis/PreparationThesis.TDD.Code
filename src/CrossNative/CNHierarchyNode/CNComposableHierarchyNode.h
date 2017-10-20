#ifndef CROSSNATIVE_COMPOSABLEHIERARCHYNODE_H
#define CROSSNATIVE_COMPOSABLEHIERARCHYNODE_H

#include "CNHierarchyNode.h"
#include <vector>

class CNComposableHierarchyNode;
typedef std::shared_ptr<CNComposableHierarchyNode> CNComposableHierarchyNodePtr;
class CNComposableHierarchyNode : public CNHierarchyNode {
public:
    static CNComposableHierarchyNodePtr getNewInstance();
    virtual  ~CNComposableHierarchyNode();

protected:
    CNComposableHierarchyNode();

public:
    virtual bool isParentOf(CNHierarchyNodePtr node) override;
    virtual int getChildCount() override;
    virtual CNHierarchyNodePtr getChild(int childPosition) override;

    virtual void add(std::shared_ptr<CNHierarchyNode> node) override;
    virtual void remove(std::shared_ptr<CNHierarchyNode> node) override;
    virtual void insert(std::shared_ptr<CNHierarchyNode> node, int childPos) override;

private:
    std::vector<CNHierarchyNodePtr> children;
};

#endif //CROSSNATIVE_COMPOSABLEHIERARCHYNODE_H