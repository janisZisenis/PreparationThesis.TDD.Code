#include "CNTagMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNTagMatcherPtr CNTagMatcher::getNewInstance(std::string tag) {
    return CNTagMatcherPtr(new CNTagMatcher(tag));
}
CNTagMatcher::~CNTagMatcher() {}
CNTagMatcher::CNTagMatcher(std::string tag) : tag(tag) {}

bool CNTagMatcher::matches(CNVisitablePtr visitable) {
    return false;
}
