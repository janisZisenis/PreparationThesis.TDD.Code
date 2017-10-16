#include "CocoaViewMatcherFactory.h"
#include <CrossNative/CNMatcher/CNTypeMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include "CocoaViews/CocoaShell/Visitors/CocoaShellNullVisitor.h"

CocoaViewMatcherFactoryPtr CocoaViewMatcherFactory::getNewInstance() {
    return CocoaViewMatcherFactoryPtr(new CocoaViewMatcherFactory());
}
CocoaViewMatcherFactory::~CocoaViewMatcherFactory() {}
CocoaViewMatcherFactory::CocoaViewMatcherFactory() {}

CNMatcherPtr CocoaViewMatcherFactory::makeTopLevelMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr CocoaViewMatcherFactory::makeShellTypeMatcher() {
    CNVisitorPtr matchingVisitor = CocoaShellNullVisitor::getNewInstance();
    return makeCNTypeMatcher(matchingVisitor);
}

CNMatcherPtr CocoaViewMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr CocoaViewMatcherFactory::makeCNTypeMatcher(CNVisitorPtr matchingVisitor) {
    return CNTypeMatcher::getNewInstance(matchingVisitor);
}
