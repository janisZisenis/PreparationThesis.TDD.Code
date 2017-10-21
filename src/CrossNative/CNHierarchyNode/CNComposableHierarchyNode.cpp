#include "CNComposableHierarchyNode.h"
#include "CNInvalidChildPositionException.h"

CNComposableHierarchyNodePtr CNComposableHierarchyNode::getNewInstance(CNVisitablePtr visitable)  {
    return CNComposableHierarchyNodePtr(new CNComposableHierarchyNode(visitable));
}
CNComposableHierarchyNode::~CNComposableHierarchyNode() {}
CNComposableHierarchyNode::CNComposableHierarchyNode(CNVisitablePtr visitable) : visitable(visitable) {}

void CNComposableHierarchyNode::add(CNHierarchyNodePtr node) {
    addToChildren(node);
}

void CNComposableHierarchyNode::remove(CNHierarchyNodePtr node) {
    if(!isParentOf(node))
        throw CNChildNotFoundException();

    removeFromChildren(findPosition(node));
}

void CNComposableHierarchyNode::insert(CNHierarchyNodePtr node, int childPos) {
    if(!isValidInsertingPosition(childPos))
        throw CNInvalidInsertingPositionException();

    insertToChildren(node, childPos);
}

void CNComposableHierarchyNode::remove(int childPos) {
    if(!isValidChildPosition(childPos))
        throw CNInvalidChildPositionException();

    removeFromChildren(childPos);
}

bool CNComposableHierarchyNode::isParentOf(CNHierarchyNodePtr node) {
    return findPosition(node) > -1;
}

int CNComposableHierarchyNode::getChildCount() {
    return (int)children.size();
}

CNHierarchyNodePtr CNComposableHierarchyNode::getChild(int childPos) {
    if(!isValidChildPosition(childPos))
        throw CNInvalidChildPositionException();

    return children[childPos];
}

void CNComposableHierarchyNode::addToChildren(CNHierarchyNodePtr node) {
    children.push_back(node);
}

void CNComposableHierarchyNode::removeFromChildren(int childPos) {
    children.erase(children.begin() + childPos);
}

int CNComposableHierarchyNode::findPosition(CNHierarchyNodePtr node) {
    std::vector<CNHierarchyNodePtr>::iterator it;
    it = std::find(children.begin(), children.end(), node);
    return it == children.end() ? -1 : (int)(it - children.begin());
}

bool CNComposableHierarchyNode::isValidInsertingPosition(int childPos) {
    return childPos <= children.size();
}

bool CNComposableHierarchyNode::isValidChildPosition(int childPos) {
    return childPos < children.size();
}

void CNComposableHierarchyNode::insertToChildren(CNHierarchyNodePtr node, int childPos) {
    children.insert(children.begin()+ childPos, node);
}

void CNComposableHierarchyNode::accept(CNVisitorPtr visitor) {

}

