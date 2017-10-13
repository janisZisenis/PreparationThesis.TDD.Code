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

    std::vector< std::shared_ptr<CNComponent> >::iterator it;
    it = std::find(children.begin(), children.end(), child);

    if(it == children.end())
        throw CNChildNotFoundException();

    children.erase(it);
}