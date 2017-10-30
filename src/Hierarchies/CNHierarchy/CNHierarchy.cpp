#include "CNHierarchy.h"
#include "Hierarchies/CNComponent/CNComponent.h"
#include "Hierarchies/CNComponent/CNComposable/CNComposable.h"
#include "Hierarchies/CNComposer/CNNullComposer.h"

CNHierarchyPtr CNHierarchy::getNewInstance()  {
    return CNHierarchyPtr(new CNHierarchy());
}
CNHierarchy::~CNHierarchy() {}
CNHierarchy::CNHierarchy() : root(CNComposable::getNewInstance(nullptr, CNNullComposer::getNewInstance())) {}

void CNHierarchy::add(CNComponentPtr node, const CNHierarchyIndex &parent) {
    find(parent)->add(node);
}

void CNHierarchy::remove(CNComponentPtr node, const CNHierarchyIndex&  parent) {
    find(parent)->remove(node);
}

void CNHierarchy::insert(CNComponentPtr node, const CNHierarchyIndex& parent, int childPos) {
    find(parent)->insert(node, childPos);
}

void CNHierarchy::remove(const CNHierarchyIndex& parent, int childPos) {
    find(parent)->remove(childPos);
}

CNComponentPtr CNHierarchy::retrieve(const CNHierarchyIndex& index) {
    return index.isValid() ? find(index) : throw CNInvalidIndexException();
}

CNComponentPtr CNHierarchy::find(const CNHierarchyIndex &index) {
    CNComponentPtr retrieved = root;

    for(int i = 0; i < index.depth(); i++) {
        if (index[i] >= retrieved->getChildCount())
            throw CNNotExistingIndexException();

        retrieved = retrieved->getChild(index[i]);
    }

    return retrieved;
}

int CNHierarchy::getChildCountFor(const CNHierarchyIndex &parent) {
    return find(parent)->getChildCount();
}

