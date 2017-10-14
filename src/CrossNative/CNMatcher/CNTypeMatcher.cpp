#include "CNTypeMatcher.h"
#include "CrossNative/CNComponent/CNComponent.h"

CNTypeMatcherPtr CNTypeMatcher::getNewInstance(std::shared_ptr<CNVisitor> matching) {
    return CNTypeMatcherPtr(new CNTypeMatcher(matching));
}

CNTypeMatcher::~CNTypeMatcher() {

}

CNTypeMatcher::CNTypeMatcher(std::shared_ptr<CNVisitor> matching)
        : matching(matching) {}

bool CNTypeMatcher::matches(CNComponentPtr component) {
    component->accept(matching);
    return false;
}
