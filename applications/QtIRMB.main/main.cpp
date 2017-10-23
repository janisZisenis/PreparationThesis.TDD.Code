#include <QApplication>

#include "QtViews/QtViewComponentFactory/QtViewComponentFactory.h"
#include "QtViews/QtViewMatcherFactory/QtViewMatcherFactory.h"

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>
#include <CrossViews/SelectionModel/SelectionModelImp.h>
#include <CrossViews/PropertiesExplorerPresenter/HierarchicModelAccess.h>

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    SelectionModelImpPtr selectionModel = SelectionModelImp::getNewInstance();
    HierarchicModelAccessPtr modelAccess = nullptr;

    QtViewComponentFactoryPtr componentFactory = QtViewComponentFactory::getNewInstance();
    QtViewMatcherFactoryPtr matcherFactory = QtViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(componentFactory->makeShellComponent(), matcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(componentFactory->makeSolutionExplorerComponent(selectionModel), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makePropertiesExplorerComponent(selectionModel, modelAccess), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makeMenuBarComponent(), matcherFactory->makeShellTypeMatcher());

    viewHierarchy->load(componentFactory->makeHelloWorldMenuComponent("hello-world-menu"), matcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(componentFactory->makeHelloWorldMenuComponent("hello-world-submenu"), matcherFactory->makeTagMatcher("hello-world-menu"));
    viewHierarchy->load(componentFactory->makeExampleActionComponent(), matcherFactory->makeTagMatcher("hello-world-submenu"));

    return a.exec();
}