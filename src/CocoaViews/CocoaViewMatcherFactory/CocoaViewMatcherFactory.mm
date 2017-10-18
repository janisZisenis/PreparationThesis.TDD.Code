#include "CocoaViewMatcherFactory.h"
#include <CrossNative/CNMatcher/CNVisitingMatcher/CNVisitingMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include <CrossNative/CNTagged/Visitors/CNTagIdentifyingVisitor.h>
#include "CocoaViews/CocoaShell/Visitors/CocoaShellTypeIdentifyingVisitor.h"
#include "CocoaViews/CocoaMenuBar/Visitors/CocoaMenuBarTypeIdentifyingVisitor.h"

CocoaViewMatcherFactoryPtr CocoaViewMatcherFactory::getNewInstance() {
    return CocoaViewMatcherFactoryPtr(new CocoaViewMatcherFactory());
}
CocoaViewMatcherFactory::~CocoaViewMatcherFactory() {}
CocoaViewMatcherFactory::CocoaViewMatcherFactory() {}

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
    CNIdentifyingVisitorPtr visitor = CNTagIdentifyingVisitor::getNewInstance(tag);
    return makeCNVisitingMatcher(visitor);
}

CNMatcherPtr CocoaViewMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr CocoaViewMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifying) {
    return CNVisitingMatcher::getNewInstance(identifying);
}
