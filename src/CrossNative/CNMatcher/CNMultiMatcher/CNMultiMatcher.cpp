#include "CNMultiMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNMultiMatcherPtr CNMultiMatcher::getNewInstance() {
    return CNMultiMatcherPtr(new CNMultiMatcher());
}

CNMultiMatcher::~CNMultiMatcher() {}

CNMultiMatcher::CNMultiMatcher() {}

bool CNMultiMatcher::matches(CNVisitablePtr visitable) {
    return true;
}
