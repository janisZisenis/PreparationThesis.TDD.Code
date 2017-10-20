#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNode.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() {}

void CNHierarchy::add(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex) {
    if(!first) {
        first = node;
    }
    else if(!second) {
        this->first->add(node);
        second = node;
    } else {
        second->add(node);
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
    if(index.depth() == 1) {
        return first;
    }
    if(index.depth() == 2)
        return first->getChild(0);

    return second->getChild(0);
}

