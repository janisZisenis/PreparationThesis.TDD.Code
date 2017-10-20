#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNode.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() {}

void CNHierarchy::add(CNHierarchyNodePtr component, CNHierarchyIndex parentIndex) {}
void CNHierarchy::remove(CNHierarchyNodePtr component, CNHierarchyIndex parentIndex) {}

void CNHierarchy::insert(CNHierarchyNodePtr component, CNHierarchyIndex parentIndex, int childPos) {

}

void CNHierarchy::remove(CNHierarchyIndex parentIndex, int childPos) {

}

int CNHierarchy::getChildCountFor(CNHierarchyIndex index) {
    return 0;
}

CNHierarchyNodePtr CNHierarchy::retrieve(CNHierarchyIndex index) {
    return CNHierarchyNodePtr();
}

CNHierarchyNodePtr CNHierarchy::findComponent(CNHierarchyIndex index) {
    return CNHierarchyNodePtr();
}
