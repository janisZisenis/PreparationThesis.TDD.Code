#include "QtViewMatcherFactory.h"
#include <Hierarchies/CNMatcherFactory/CNMatcherFactory.h>
#include <Hierarchies/CNMatcher/CNMatcher.h>

#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellTypeIdentifyingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarTypeIdentifyingVisitor.h"

QtViewMatcherFactoryPtr QtViewMatcherFactory::getNewInstance() {
    return QtViewMatcherFactoryPtr(new QtViewMatcherFactory());
}
QtViewMatcherFactory::~QtViewMatcherFactory() {}
QtViewMatcherFactory::QtViewMatcherFactory() : matcherFactory(CNMatcherFactory::getNewInstance()) {}

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
    return matcherFactory->makeCNTagMatcher(tag);
}

CNMatcherPtr QtViewMatcherFactory::makeCNNullMatcher() {
    return matcherFactory->makeCNNullMatcher();
}

CNMatcherPtr QtViewMatcherFactory::makeCNVisitingMatcher(CNIdentifyingVisitorPtr identifier) {
    return matcherFactory->makeCNVisitingMatcher(identifier);
}

