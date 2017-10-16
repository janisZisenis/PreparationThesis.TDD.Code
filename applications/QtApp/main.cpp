#include <QApplication>

#include "QtViews/QtViewComponentFactory/QtViewComponentFactory.h"
#include "QtViews/QtViewMatcherFactory/QtViewMatcherFactory.h"

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtViewComponentFactoryPtr componentFactory = QtViewComponentFactory::getNewInstance();
    QtViewMatcherFactoryPtr matcherFactory = QtViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(componentFactory->makeShellComponent(), matcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(componentFactory->makeSolutionExplorerComponent(), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makePropertiesExplorerComponent(), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makeMenuBarComponent(), matcherFactory->makeShellTypeMatcher());

    return a.exec();
}