#include "CNVisitingMatcher.h"
#include "CNIdentifyingVisitor.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNVisitingMatcherPtr CNVisitingMatcher::getNewInstance(CNIdentifyingVisitorPtr identifyingVisitor) {
    return CNVisitingMatcherPtr(new CNVisitingMatcher(identifyingVisitor));
}

CNVisitingMatcher::~CNVisitingMatcher() {

}

CNVisitingMatcher::CNVisitingMatcher(CNIdentifyingVisitorPtr identifyingVisitor)
        : identifyingVisitor(identifyingVisitor) {}

bool CNVisitingMatcher::matches(CNVisitablePtr visitable) {
    try {
        visitable->accept(identifyingVisitor);
    } catch(CNVisitableVisitorMismatchException &e) {
        return false;
    }

    return identifyingVisitor->hasIdentified();
}
