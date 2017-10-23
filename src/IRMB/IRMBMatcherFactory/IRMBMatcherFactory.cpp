#include "IRMBMatcherFactory.h"
#include <CrossNative/CNMatcher/CNMultiMatcher/CNMultiMatcher.h>
#include <CrossNative/CNMatcher/CNVisitingMatcher/CNVisitingMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include <IRMB/STLFile/Visitors/STLFileTypeIdentifyingVisitor.h>
#include <IRMB/GridGenerator/Visitors/GridGeneratorTypeIdentifyingVisitor.h>

IRMBMatcherFactoryPtr IRMBMatcherFactory::getNewInstance() {
    return IRMBMatcherFactoryPtr(new IRMBMatcherFactory());
}
IRMBMatcherFactory::~IRMBMatcherFactory() {}
IRMBMatcherFactory::IRMBMatcherFactory() {}

CNMatcherPtr IRMBMatcherFactory::makeGridGeneratorChildTypeMatcher() {
    CNMultiMatcherPtr multiMatcher = makeCNMultiMatcher();
    multiMatcher->add(makeCNVisitingMatcher(makeSTLFileIdentifyingVisitor()));
    return multiMatcher;
}

CNMatcherPtr IRMBMatcherFactory::makeGridGeneratorParentTypeMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr IRMBMatcherFactory::makeSTLFileChildTypeMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr IRMBMatcherFactory::makeSTLFileParentTypeMatcher() {
    CNMultiMatcherPtr multiMatcher = makeCNMultiMatcher();
    multiMatcher->add(makeCNVisitingMatcher(makeGridGeneratorIdentifyingVisitor()));
    return multiMatcher;
}

CNIdentifyingVisitorPtr IRMBMatcherFactory::makeSTLFileIdentifyingVisitor() {
    return STLFileTypeIdentifyingVisitor::getNewInstance();
}

CNIdentifyingVisitorPtr IRMBMatcherFactory::makeGridGeneratorIdentifyingVisitor() {
    return GridGeneratorTypeIdentifyingVisitor::getNewInstance();
}

CNMultiMatcherPtr IRMBMatcherFactory::makeCNMultiMatcher() {
    return CNMultiMatcher::getNewInstance();
}

CNMatcherPtr IRMBMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr visitor) {
    return CNVisitingMatcher::getNewInstance(visitor);
}

CNMatcherPtr IRMBMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}
