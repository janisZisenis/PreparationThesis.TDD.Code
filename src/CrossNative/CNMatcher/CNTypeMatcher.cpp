#include "CNTypeMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"

CNTypeMatcherPtr CNTypeMatcher::getNewInstance(std::shared_ptr<CNVisitor> typeIdentifier) {
    return CNTypeMatcherPtr(new CNTypeMatcher(typeIdentifier));
}

CNTypeMatcher::~CNTypeMatcher() {

}

CNTypeMatcher::CNTypeMatcher(std::shared_ptr<CNVisitor> matching)
        : typeIdentifier(matching) {}

bool CNTypeMatcher::matches(CNVisitablePtr visitable) {
    try {
        visitable->accept(typeIdentifier);
    } catch (CNVisitableVisitorMismatchException &e) {
        return false;
    }

    return true;
}
