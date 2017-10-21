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
    virtual CNHierarchyNodePtr getChild(int childPos) override;

    virtual void add(std::shared_ptr<CNHierarchyNode> node) override;
    virtual void remove(std::shared_ptr<CNHierarchyNode> node) override;
    virtual void insert(std::shared_ptr<CNHierarchyNode> node, int childPos) override;
    virtual void remove(int childPos) override;
private:
    virtual bool isValidInsertingPosition(int childPos);
    virtual bool isValidChildPosition(int childPos);
    virtual void addToChildren(CNHierarchyNodePtr node);
    virtual void insertToChildren(CNHierarchyNodePtr node, int childPos);
    virtual void removeFromChildren(int childPos);
    virtual int findPosition(CNHierarchyNodePtr node);

private:

    std::vector<CNHierarchyNodePtr> children;
};

#endif //CROSSNATIVE_COMPOSABLEHIERARCHYNODE_H