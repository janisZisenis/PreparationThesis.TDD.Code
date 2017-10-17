#include "CNTagMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNTagMatcherPtr CNTagMatcher::getNewInstance() {
    return CNTagMatcherPtr(new CNTagMatcher());
}
CNTagMatcher::~CNTagMatcher() {}
CNTagMatcher::CNTagMatcher(){}

bool CNTagMatcher::matches(CNVisitablePtr visitable) {
    return false;
}
