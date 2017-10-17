#include "CNTagMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CrossNative/CNTagged/CNTagged.h"

CNTagMatcher::CNTagIdentifierPtr CNTagMatcher::CNTagIdentifier::getNewInstance() {
    return CNTagMatcher::CNTagIdentifierPtr(new CNTagMatcher::CNTagIdentifier());
}
CNTagMatcher::CNTagIdentifier::~CNTagIdentifier() {}
CNTagMatcher::CNTagIdentifier::CNTagIdentifier() {}

void CNTagMatcher::CNTagIdentifier::visit(CNTaggedPtr tagged) {
    identifiedTag = tagged->getTag();
}

std::string CNTagMatcher::CNTagIdentifier::getIdentifiedTag() {
    return identifiedTag;
}


CNTagMatcherPtr CNTagMatcher::getNewInstance(std::string tag) {
    return CNTagMatcherPtr(new CNTagMatcher(tag));
}
CNTagMatcher::~CNTagMatcher() {}
CNTagMatcher::CNTagMatcher(std::string tag) : tag(tag) {}

bool CNTagMatcher::matches(CNVisitablePtr visitable) {
    CNTagIdentifierPtr tagIdentifier = CNTagIdentifier::getNewInstance();

    try {
        visitable->accept(tagIdentifier);
    } catch(CNVisitableVisitorMismatchException &e) {
        return false;
    }

    return tag == tagIdentifier->getIdentifiedTag();
}