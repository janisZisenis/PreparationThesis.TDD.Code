#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNode.h"
#include "CrossNative/CNHierarchyNode/CNComposableHierarchyNode.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() : root(CNComposableHierarchyNode::getNewInstance()) {}

void CNHierarchy::add(CNHierarchyNodePtr node, CNHierarchyIndex parent) {
    find(parent)->add(node);
}

void CNHierarchy::remove(CNHierarchyNodePtr node, CNHierarchyIndex parent) {
    throw CNNotExistingIndexException();
}

void CNHierarchy::insert(CNHierarchyNodePtr node, CNHierarchyIndex parent, int childPos) {}

void CNHierarchy::remove(CNHierarchyIndex parent, int childPos) {}

CNHierarchyNodePtr CNHierarchy::retrieve(const CNHierarchyIndex& index) {
    return index.isValid() ? find(index) : throw CNInvalidIndexException();
}

CNHierarchyNodePtr CNHierarchy::find(const CNHierarchyIndex &index) {
    CNHierarchyNodePtr retrieved = root;

    for(int i = 0; i < index.depth(); i++) {
        if (index[i] >= retrieved->getChildCount())
            throw CNNotExistingIndexException();

        retrieved = retrieved->getChild(index[i]);
    }

    return retrieved;
}

