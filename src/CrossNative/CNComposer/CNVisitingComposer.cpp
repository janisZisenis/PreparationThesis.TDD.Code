#include "CNVisitingComposer.h"
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CrossNative/CNComponent/CNComponent.h"

CNVisitingComposerPtr CNVisitingComposer::getNewInstance(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return CNVisitingComposerPtr(new CNVisitingComposer(composing, decomposing));
}

CNVisitingComposer::~CNVisitingComposer() {}

CNVisitingComposer::CNVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing){}

void CNVisitingComposer::mount(CNComponentPtr component) {}

void CNVisitingComposer::dismount(CNComponentPtr component) {}
