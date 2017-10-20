#include "CNHierarchy.h"
#include "CrossNative/CNHierarchyNode/CNHierarchyNode.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() {}

void CNHierarchy::add(CNHierarchyNodePtr node, CNHierarchyIndex parentIndex) {
    if(!parentIndex.isValid()) {
        nodes.push_back(node);
    } else {
        if (parentIndex.depth() == 1)
            nodes[0]->add(node);
        else if(parentIndex.depth() == 2)
            nodes[0]->getChild(0)->add(node);
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
    if(index.depth() == 1)
        return nodes[index[0]];

    return nodes[0]->getChild(index[1]);
}

