#include "CNComposable.h"

#include "CrossNative/CNComposer/CNComposer.h"

CNComposablePtr CNComposable::getNewInstance(CNComposerPtr composer) {
    return CNComposablePtr(new CNComposable(composer));
}

CNComposable::~CNComposable() {}

CNComposable::CNComposable(CNComposerPtr composer) : composer(composer) {}

void CNComposable::add(std::shared_ptr<CNComponent> component) {
    composer->mount(component);
}

void CNComposable::remove(std::shared_ptr<CNComponent> component) {

}