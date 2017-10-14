#include "CNTypeComposer.h"
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CrossNative/CNComponent/CNComponent.h"

CNTypeComposerPtr CNTypeComposer::getNewInstance(CNVisitorPtr mounting, CNVisitorPtr dismounting) {
    return CNTypeComposerPtr(new CNTypeComposer(mounting, dismounting));
}

CNTypeComposer::~CNTypeComposer() {}

CNTypeComposer::CNTypeComposer(CNVisitorPtr mounting, CNVisitorPtr dismounting)
        : mounting(mounting), dismounting(dismounting) {}

void CNTypeComposer::mount(CNComponentPtr component) {
    component->accept(mounting);
}

void CNTypeComposer::dismount(CNComponentPtr component) {
    component->accept(dismounting);
}
