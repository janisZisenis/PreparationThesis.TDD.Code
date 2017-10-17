#include "CNTagMatcher.h"
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CrossNative/CNTagged/CNTagged.h"

CNTagMatcher::CNTagIdentifierPtr CNTagMatcher::CNTagIdentifier::getNewInstance(std::string tag) {
    return CNTagMatcher::CNTagIdentifierPtr(new CNTagMatcher::CNTagIdentifier(tag));
}
CNTagMatcher::CNTagIdentifier::~CNTagIdentifier() {}
CNTagMatcher::CNTagIdentifier::CNTagIdentifier(std::string tag) : tag(tag) {}

void CNTagMatcher::CNTagIdentifier::visit(CNTaggedPtr tagged) {
    identifiedTag = tagged->getTag();
}

bool CNTagMatcher::CNTagIdentifier::hasIdentified() {
    return tag == identifiedTag;
}


CNTagMatcherPtr CNTagMatcher::getNewInstance(std::string tag) {
    return CNTagMatcherPtr(new CNTagMatcher(tag));
}
CNTagMatcher::~CNTagMatcher() {}
CNTagMatcher::CNTagMatcher(std::string tag)
        : tag(tag),
          visitor(CNTagMatcher::CNTagIdentifier::getNewInstance(tag)) {}

bool CNTagMatcher::matches(CNVisitablePtr visitable) {
    try {
        visitable->accept(visitor);
    } catch(CNVisitableVisitorMismatchException &e) {
        return false;
    }

    return visitor->hasIdentified();
}