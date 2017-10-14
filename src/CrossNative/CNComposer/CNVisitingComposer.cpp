#include "CNVisitingComposer.h"
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CrossNative/CNComponent/CNComponent.h"

CNVisitingComposerPtr CNVisitingComposer::getNewInstance(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return CNVisitingComposerPtr(new CNVisitingComposer(composing, decomposing));
}

CNVisitingComposer::~CNVisitingComposer() {}

CNVisitingComposer::CNVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing)
        : composing(composing) {}

void CNVisitingComposer::mount(CNComponentPtr component) {
    component->accept(composing);
}

void CNVisitingComposer::dismount(CNComponentPtr component) {}
