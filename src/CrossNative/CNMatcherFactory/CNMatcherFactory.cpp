#include "CNMatcherFactory.h"
#include "CrossNative/CNMatcher/CNNullMatcher.h"
#include "CrossNative/CNMatcher/CNVisitingMatcher/CNVisitingMatcher.h"
#include "CrossNative/CNMatcher/CNMultiMatcher/CNMultiMatcher.h"

CNMatcherFactoryPtr CNMatcherFactory::getNewInstance() {
    return CNMatcherFactoryPtr(new CNMatcherFactory());
}
CNMatcherFactory::~CNMatcherFactory() {}
CNMatcherFactory::CNMatcherFactory() {}

CNMatcherPtr CNMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr CNMatcherFactory::makeCNVisitingMatcher(std::shared_ptr<CNIdentifyingVisitor> identifier) {
    return CNVisitingMatcher::getNewInstance(identifier);
}

CNMatcherPtr CNMatcherFactory::makeCNMultiMatcher(std::vector<CNMatcherPtr> matchers) {
    CNMultiMatcherPtr matcher = CNMultiMatcher::getNewInstance();

    for(int i = 0; i < matchers.size(); i++)
        matcher->add(matchers[i]);

    return matcher;
}
