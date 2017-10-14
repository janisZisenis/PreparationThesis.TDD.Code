#include "CNTypeMatcher.h"
#include "CrossNative/CNComponent/CNComponent.h"

CNTypeMatcherPtr CNTypeMatcher::getNewInstance(std::shared_ptr<CNVisitor> identifying) {
    return CNTypeMatcherPtr(new CNTypeMatcher(identifying));
}

CNTypeMatcher::~CNTypeMatcher() {

}

CNTypeMatcher::CNTypeMatcher(std::shared_ptr<CNVisitor> identifying) {}

bool CNTypeMatcher::matches(CNComponentPtr component) {
    return false;
}
