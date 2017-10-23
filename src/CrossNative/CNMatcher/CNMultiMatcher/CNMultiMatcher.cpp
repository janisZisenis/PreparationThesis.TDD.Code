#include "CNMultiMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNMultiMatcherPtr CNMultiMatcher::getNewInstance() {
    return CNMultiMatcherPtr(new CNMultiMatcher());
}

CNMultiMatcher::~CNMultiMatcher() {}

CNMultiMatcher::CNMultiMatcher() {}

bool CNMultiMatcher::matches(CNVisitablePtr visitable) {
    if(matchers.empty()) return false;
    return matchers[0]->matches(visitable);
}

void CNMultiMatcher::add(CNMatcherPtr matcher) {
    matchers.push_back(matcher);
}
