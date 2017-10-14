#include "CNComposable.h"

#include "CrossNative/CNComposer/CNComposer.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNComposablePtr CNComposable::getNewInstance(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposablePtr(new CNComposable(visitable, composer));
}

CNComposable::~CNComposable() {
    std::vector< CNComponentPtr >::iterator it;
    for(it = children.begin(); it < children.end(); it++)
        composer->dismount(*it);
}

CNComposable::CNComposable(CNVisitablePtr visitable, CNComposerPtr composer)
        : visitable(visitable), composer(composer) {}

void CNComposable::add(CNComponentPtr child) {
    mount(child);
    addToChildren(child);
}

void CNComposable::remove(CNComponentPtr child) {
    if(!isParentOf(child))
        throw CNChildNotFoundException();

    dismount(child);
    removeFromChildren(child);
}

bool CNComposable::isParentOf(CNComponentPtr component) {
    return findPosition(component) > -1;
}

void CNComposable::accept(std::shared_ptr<CNVisitor> visitor) {
    visitable->accept(visitor);
}

void CNComposable::addToChildren(CNComponentPtr child) {
    children.push_back(child);
}

void CNComposable::removeFromChildren(CNComponentPtr child) {
    children.erase(children.begin() + findPosition(child));
}

void CNComposable::mount(CNComponentPtr component) {
    composer->mount(component);
}

void CNComposable::dismount(CNComponentPtr component) {
    composer->dismount(component);
}

int CNComposable::findPosition(CNComponentPtr component) {
    std::vector< CNComponentPtr >::iterator it;
    it = std::find(children.begin(), children.end(), component);

    return it == children.end() ? -1 : (int)(it - children.begin());
}
