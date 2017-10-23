#include "CNMultiMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNMultiMatcherPtr CNMultiMatcher::getNewInstance() {
    return CNMultiMatcherPtr(new CNMultiMatcher());
}

CNMultiMatcher::~CNMultiMatcher() {}

CNMultiMatcher::CNMultiMatcher() {}

bool CNMultiMatcher::matches(CNVisitablePtr visitable) {
    if(matchers.empty()) return false;

    for(int i = 0; i < matchers.size(); i++)
        if(matchers[i]->matches(visitable))
            return true;

    return false;
}

void CNMultiMatcher::add(CNMatcherPtr matcher) {
    matchers.push_back(matcher);
}
