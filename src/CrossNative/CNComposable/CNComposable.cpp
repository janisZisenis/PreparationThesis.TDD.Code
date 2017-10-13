#include "CNComposable.h"

#include "CrossNative/CNComposer/CNComposer.h"

CNComposablePtr CNComposable::getNewInstance(CNComposerPtr composer) {
    return CNComposablePtr(new CNComposable(composer));
}

CNComposable::~CNComposable() {}

CNComposable::CNComposable(CNComposerPtr composer) : composer(composer) {}

void CNComposable::add(std::shared_ptr<CNComponent> child) {
    composer->mount(child);
    children.push_back(child);
}

void CNComposable::remove(std::shared_ptr<CNComponent> child) {
    composer->dismount(child);

    if(!isParentOf(child))
        throw CNChildNotFoundException();

    children.erase(children.begin() + findPosition(child));
}

bool CNComposable::isParentOf(std::shared_ptr<CNComponent> component) {
    return findPosition(component) > -1;
}

int CNComposable::findPosition(std::shared_ptr<CNComponent> component) {
    std::vector< std::shared_ptr<CNComponent> >::iterator it;
    it = std::find(children.begin(), children.end(), component);

    return it == children.end() ? -1 : (int)(it - children.begin());
}
