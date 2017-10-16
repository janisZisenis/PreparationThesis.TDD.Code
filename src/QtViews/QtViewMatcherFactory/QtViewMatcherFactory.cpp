#include "QtViewMatcherFactory.h"
#include <CrossNative/CNMatcher/CNTypeMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include "QtViews/QtShell/Visitors/QtShellNullVisitor.h"

QtViewMatcherFactoryPtr QtViewMatcherFactory::getNewInstance() {
    return QtViewMatcherFactoryPtr(new QtViewMatcherFactory());
}
QtViewMatcherFactory::~QtViewMatcherFactory() {}
QtViewMatcherFactory::QtViewMatcherFactory() {}

CNMatcherPtr QtViewMatcherFactory::makeTopLevelMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr QtViewMatcherFactory::makeShellTypeMatcher() {
    CNVisitorPtr matchingVisitor = CocoaShellNullVisitor::getNewInstance();
    return makeCNTypeMatcher(matchingVisitor);
}

CNMatcherPtr QtViewMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr QtViewMatcherFactory::makeCNTypeMatcher(CNVisitorPtr matchingVisitor) {
    return CNTypeMatcher::getNewInstance(matchingVisitor);
}
