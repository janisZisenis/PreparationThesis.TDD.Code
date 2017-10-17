#include "QtViewMatcherFactory.h"
#include <CrossNative/CNMatcher/CNVisitingMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include "QtViews/QtShell/Visitors/QtShellTypeIdentifyingVisitor.h"

QtViewMatcherFactoryPtr QtViewMatcherFactory::getNewInstance() {
    return QtViewMatcherFactoryPtr(new QtViewMatcherFactory());
}
QtViewMatcherFactory::~QtViewMatcherFactory() {}
QtViewMatcherFactory::QtViewMatcherFactory() {}

CNMatcherPtr QtViewMatcherFactory::makeTopLevelMatcher() {
    return makeCNNullMatcher();
}

CNMatcherPtr QtViewMatcherFactory::makeShellTypeMatcher() {
    CNIdentifyingVisitorPtr identifying = QtShellTypeIdentifyingVisitor::getNewInstance();
    return makeCNVisitingMatcher(identifying);
}

CNMatcherPtr QtViewMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr QtViewMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifying) {
    return CNVisitingMatcher::getNewInstance(identifying);
}
