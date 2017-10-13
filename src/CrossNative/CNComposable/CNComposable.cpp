#include "CNComposable.h"

#include "CrossNative/CNComposer/CNComposer.h"

CNComposablePtr CNComposable::getNewInstance(CNComposerPtr composer) {
    return CNComposablePtr(new CNComposable(composer));
}

CNComposable::~CNComposable() {}

CNComposable::CNComposable(CNComposerPtr composer) : composer(composer) {}

void CNComposable::add(CNComponentPtr child) {
    composer->mount(child);
    children.push_back(child);
}

void CNComposable::remove(CNComponentPtr child) {
    composer->dismount(child);

    if(!isParentOf(child))
        throw CNChildNotFoundException();

    children.erase(children.begin() + findPosition(child));
}

bool CNComposable::isParentOf(CNComponentPtr component) {
    return findPosition(component) > -1;
}

int CNComposable::findPosition(CNComponentPtr component) {
    std::vector< CNComponentPtr >::iterator it;
    it = std::find(children.begin(), children.end(), component);

    return it == children.end() ? -1 : (int)(it - children.begin());
}
