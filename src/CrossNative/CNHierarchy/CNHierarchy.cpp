#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNode.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() {}

void CNHierarchy::add(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex) {
    if(this->node) {
        this->node->add(node);
    } else {
        this->node = node;
    }
}
void CNHierarchy::remove(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex) {}

void CNHierarchy::insert(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex, int childPos) {

}

void CNHierarchy::remove(CNHierarchyIndex parentIndex, int childPos) {

}

int CNHierarchy::getChildCountFor(CNHierarchyIndex index) {
    return 0;
}

CNHierarchyNodePtr CNHierarchy::retrieve(CNHierarchyIndex index) {
    return node;
}

