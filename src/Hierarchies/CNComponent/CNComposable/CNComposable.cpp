#include "CNComposable.h"
#include "Hierarchies/CNComponent/CNInvalidChildPositionException.h"
#include "Hierarchies/CNComposer/CNComposer.h"

CNComposablePtr CNComposable::getNewInstance(CNVisitablePtr visitable, CNComposerPtr composer)  {
    return CNComposablePtr(new CNComposable(visitable, composer));
}
CNComposable::~CNComposable() {
    dismountAllChildren();
}
CNComposable::CNComposable(CNVisitablePtr visitable, CNComposerPtr composer)
        : visitable(visitable), composer(composer) {}

void CNComposable::add(CNComponentPtr component) {
    mount(component);
    addToChildren(component);
}

void CNComposable::remove(CNComponentPtr component) {
    if(!isParentOf(component))
        throw CNChildNotFoundException();

    dismount(component);
    removeFromChildren(findPosition(component));
}

void CNComposable::insert(CNComponentPtr component, int childPos) {
    if(!isValidInsertingPosition(childPos))
        throw CNInvalidInsertingPositionException();

    mount(component);
    insertToChildren(component, childPos);
}

void CNComposable::remove(int childPos) {
    if(!isValidChildPosition(childPos))
        throw CNInvalidChildPositionException();

    dismount(getChild(childPos));
    removeFromChildren(childPos);
}

bool CNComposable::isParentOf(CNComponentPtr component) {
    return findPosition(component) > -1;
}

int CNComposable::getChildCount() {
    return (int)children.size();
}

CNComponentPtr CNComposable::getChild(int childPos) {
    if(!isValidChildPosition(childPos))
        throw CNInvalidChildPositionException();

    return children[childPos];
}

void CNComposable::addToChildren(CNComponentPtr component) {
    children.push_back(component);
}

void CNComposable::removeFromChildren(int childPos) {
    children.erase(children.begin() + childPos);
}

int CNComposable::findPosition(CNComponentPtr component) {
    std::vector<CNComponentPtr>::iterator it;
    it = std::find(children.begin(), children.end(), component);
    return it == children.end() ? -1 : (int)(it - children.begin());
}

bool CNComposable::isValidInsertingPosition(int childPos) {
    return childPos <= children.size();
}

bool CNComposable::isValidChildPosition(int childPos) {
    return childPos < children.size();
}

void CNComposable::insertToChildren(CNComponentPtr component, int childPos) {
    children.insert(children.begin()+ childPos, component);
}

void CNComposable::accept(CNVisitorPtr visitor) {
    visitable->accept(visitor);
}

void CNComposable::mount(CNComponentPtr component) {
    composer->mount(component);
}

void CNComposable::dismount(CNComponentPtr component) {
    composer->dismount(component);
}

void CNComposable::dismountAllChildren() {
    for(int i = 0; i < getChildCount(); i++)
        composer->dismount(getChild(i));
}

