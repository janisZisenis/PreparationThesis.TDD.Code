#include "CNComposableHierarchyNode.h"

CNComposableHierarchyNodePtr CNComposableHierarchyNode::getNewInstance()  {
    return CNComposableHierarchyNodePtr(new CNComposableHierarchyNode());
}
CNComposableHierarchyNode::~CNComposableHierarchyNode() {}
CNComposableHierarchyNode::CNComposableHierarchyNode() {}

void CNComposableHierarchyNode::add(CNHierarchyNodePtr node) {

}

void CNComposableHierarchyNode::remove(CNHierarchyNodePtr node) {

}

void CNComposableHierarchyNode::insert(CNHierarchyNodePtr node, int childPos) {

}

bool CNComposableHierarchyNode::isParentOf(CNHierarchyNodePtr node) {
    return false;
}
