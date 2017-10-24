#include "CocoaViewMatcherFactory.h"
#include <CrossNative/CNMatcherFactory/CNMatcherFactory.h>
#include <CrossNative/CNMatcher/CNMatcher.h>

#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellTypeIdentifyingVisitor.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarTypeIdentifyingVisitor.h"

CocoaViewMatcherFactoryPtr CocoaViewMatcherFactory::getNewInstance() {
    return CocoaViewMatcherFactoryPtr(new CocoaViewMatcherFactory());
}
CocoaViewMatcherFactory::~CocoaViewMatcherFactory() {}
CocoaViewMatcherFactory::CocoaViewMatcherFactory() : matcherFactory(CNMatcherFactory::getNewInstance()) {}

CNMatcherPtr CocoaViewMatcherFactory::makeTopLevelMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr CocoaViewMatcherFactory::makeShellTypeMatcher() {
    CNIdentifyingVisitorPtr identifying = CocoaShellTypeIdentifyingVisitor::getNewInstance();
    return makeCNVisitingMatcher(identifying);
}

CNMatcherPtr CocoaViewMatcherFactory::makeMenuBarTypeMatcher() {
    CNIdentifyingVisitorPtr identifying = CocoaMenuBarTypeIdentifyingVisitor::getNewInstance();
    return makeCNVisitingMatcher(identifying);
}

CNMatcherPtr CocoaViewMatcherFactory::makeTagMatcher(std::string tag) {
    return matcherFactory->makeCNTagMatcher(tag);
}

CNMatcherPtr CocoaViewMatcherFactory::makeCNNullMatcher() {
    return matcherFactory->makeCNNullMatcher();
}

CNMatcherPtr CocoaViewMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifier) {
    return matcherFactory->makeCNVisitingMatcher(identifier);
}
