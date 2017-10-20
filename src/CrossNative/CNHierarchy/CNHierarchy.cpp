#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNode.h"
#include "CrossNative/CNHierarchyNode/CNComposableHierarchyNode.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() : root(CNComposableHierarchyNode::getNewInstance()) {}

void CNHierarchy::add(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex) {
    parentIndex.isValid() ? retrieve(parentIndex)->add(node) : root->add(node);
}

void CNHierarchy::remove(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex) {}

void CNHierarchy::insert(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex, int childPos) {

}

void CNHierarchy::remove(CNHierarchyIndex parentIndex, int childPos) {

}

CNHierarchyNodePtr CNHierarchy::retrieve(CNHierarchyIndex index) {
    CNHierarchyNodePtr retrieved = root;

    for(int i = 0; i < index.depth(); i++)
        retrieved = retrieved->getChild(index[i]);

    return retrieved;
}

