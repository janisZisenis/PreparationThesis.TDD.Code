#include "CNMultiMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNMultiMatcherPtr CNMultiMatcher::getNewInstance() {
    return CNMultiMatcherPtr(new CNMultiMatcher());
}

CNMultiMatcher::~CNMultiMatcher() {}

CNMultiMatcher::CNMultiMatcher() {}

bool CNMultiMatcher::matches(CNVisitablePtr visitable) {
    bool matches = false;
    for(int i = 0; i < matchers.size(); i++)
        matches = matches || matchers[i]->matches(visitable);
    return matches;
}

void CNMultiMatcher::add(CNMatcherPtr matcher) {
    matchers.push_back(matcher);
}
