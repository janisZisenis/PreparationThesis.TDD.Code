#include "CNVisitingComposer.h"
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CrossNative/CNComponent/CNComponent.h"

CNVisitingComposerPtr CNVisitingComposer::getNewInstance(CNVisitorPtr mounting, CNVisitorPtr dismounting) {
    return CNVisitingComposerPtr(new CNVisitingComposer(mounting, dismounting));
}

CNVisitingComposer::~CNVisitingComposer() {}

CNVisitingComposer::CNVisitingComposer(CNVisitorPtr mounting, CNVisitorPtr dismounting)
        : mounting(mounting), dismounting(dismounting) {}

void CNVisitingComposer::mount(CNVisitablePtr visitable) {
    visitable->accept(mounting);
}

void CNVisitingComposer::dismount(CNVisitablePtr visitable) {
    visitable->accept(dismounting);
}