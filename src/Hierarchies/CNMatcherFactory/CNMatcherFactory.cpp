#include "CNMatcherFactory.h"
#include "Hierarchies/CNMatcher/CNNullMatcher.h"
#include "Hierarchies/CNMatcher/CNVisitingMatcher/CNVisitingMatcher.h"
#include "Hierarchies/CNMatcher/CNMultiMatcher/CNMultiMatcher.h"
#include "Hierarchies/CNTagged/Visitors/CNTagIdentifyingVisitor.h"

CNMatcherFactoryPtr CNMatcherFactory::getNewInstance() {
    return CNMatcherFactoryPtr(new CNMatcherFactory());
}
CNMatcherFactory::~CNMatcherFactory() {}
CNMatcherFactory::CNMatcherFactory() {}

CNMatcherPtr CNMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr CNMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifier) {
    return CNVisitingMatcher::getNewInstance(identifier);
}

CNMatcherPtr CNMatcherFactory::makeCNMultiMatcher(std::vector<CNMatcherPtr> matchers) {
    CNMultiMatcherPtr matcher = CNMultiMatcher::getNewInstance();

    for(int i = 0; i < matchers.size(); i++)
        matcher->add(matchers[i]);

    return matcher;
}

CNMatcherPtr CNMatcherFactory::makeCNTagMatcher(std::string tag) {
    CNIdentifyingVisitorPtr tagIdentifier = CNTagIdentifyingVisitor::getNewInstance(tag);
    return makeCNVisitingMatcher(tagIdentifier);
}
