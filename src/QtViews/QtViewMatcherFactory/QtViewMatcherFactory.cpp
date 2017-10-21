#include "QtViewMatcherFactory.h"
#include <CrossNative/CNMatcher/CNVisitingMatcher/CNVisitingMatcher.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>

#include <CrossNative/CNTagged/Visitors/CNTagIdentifyingVisitor.h>
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellTypeIdentifyingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarTypeIdentifyingVisitor.h"

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

CNMatcherPtr QtViewMatcherFactory::makeMenuBarTypeMatcher() {
    CNIdentifyingVisitorPtr identifying = QtMenuBarTypeIdentifyingVisitor::getNewInstance();
    return makeCNVisitingMatcher(identifying);
}

CNMatcherPtr QtViewMatcherFactory::makeTagMatcher(std::string tag) {
    CNIdentifyingVisitorPtr visitor = CNTagIdentifyingVisitor::getNewInstance(tag);
    return makeCNVisitingMatcher(visitor);
}

CNMatcherPtr QtViewMatcherFactory::makeCNNullMatcher() {
    return CNNullMatcher::getNewInstance();
}

CNMatcherPtr QtViewMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifying) {
    return CNVisitingMatcher::getNewInstance(identifying);
}
