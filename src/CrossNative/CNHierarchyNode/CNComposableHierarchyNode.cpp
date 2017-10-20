#include "CNComposableHierarchyNode.h"

CNComposableHierarchyNodePtr CNComposableHierarchyNode::getNewInstance()  {
    return CNComposableHierarchyNodePtr(new CNComposableHierarchyNode());
}
CNComposableHierarchyNode::~CNComposableHierarchyNode() {}
CNComposableHierarchyNode::CNComposableHierarchyNode() {}

void CNComposableHierarchyNode::add(CNHierarchyNodePtr node) {
    children.push_back(node);
}

void CNComposableHierarchyNode::remove(CNHierarchyNodePtr node) {
    if(!isParentOf(node))
        throw CNChildNotFoundException();

    children.erase(std::find(children.begin(), children.end(), node));
}

void CNComposableHierarchyNode::insert(CNHierarchyNodePtr node, int childPos) {
    if(childPos > children.size())
        throw CNInvalidInsertingPositionException();

    children.push_back(node);
}

bool CNComposableHierarchyNode::isParentOf(CNHierarchyNodePtr node) {
    return std::find(children.begin(), children.end(), node) != children.end();
}

int CNComposableHierarchyNode::getChildCount() {
    return (int)children.size();
}

CNHierarchyNodePtr CNComposableHierarchyNode::getChild(int childPosition) {
    return nullptr;
}
