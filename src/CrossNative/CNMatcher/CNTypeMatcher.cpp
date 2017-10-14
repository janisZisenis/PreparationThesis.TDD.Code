#include "CNTypeMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNTypeMatcherPtr CNTypeMatcher::getNewInstance(std::shared_ptr<CNVisitor> matching) {
    return CNTypeMatcherPtr(new CNTypeMatcher(matching));
}

CNTypeMatcher::~CNTypeMatcher() {

}

CNTypeMatcher::CNTypeMatcher(std::shared_ptr<CNVisitor> matching)
        : matching(matching) {}

bool CNTypeMatcher::matches(CNVisitablePtr visitable) {
    visitable->accept(matching);
    return false;
}
