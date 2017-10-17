#include "CNVisitingMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNVisitingMatcherPtr CNVisitingMatcher::getNewInstance(std::shared_ptr<CNIdentifyingVisitor> identifyingVisitor) {
    return CNVisitingMatcherPtr(new CNVisitingMatcher(identifyingVisitor));
}

CNVisitingMatcher::~CNVisitingMatcher() {

}

CNVisitingMatcher::CNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifyingVisitor)
        : identifyingVisitor(identifyingVisitor) {}

bool CNVisitingMatcher::matches(CNVisitablePtr visitable) {
    return false;
}
