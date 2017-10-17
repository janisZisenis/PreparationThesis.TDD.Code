#include <QApplication>

#include "QtViews/QtViewComponentFactory/QtViewComponentFactory.h"
#include "QtViews/QtViewMatcherFactory/QtViewMatcherFactory.h"

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include "QtViews/QtMenu/QtMenu.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtViewComponentFactoryPtr componentFactory = QtViewComponentFactory::getNewInstance();
    QtViewMatcherFactoryPtr matcherFactory = QtViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(componentFactory->makeShellComponent(), matcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(componentFactory->makeSolutionExplorerComponent(), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makePropertiesExplorerComponent(), matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(componentFactory->makeMenuBarComponent(), matcherFactory->makeShellTypeMatcher());

    QtMenuPtr menu = QtMenu::getNewInstance("HelloWorld!");
    CNComposerPtr menuComposer = CNNullComposer::getNewInstance();
    CNComposablePtr menuComposable = CNComposable::getNewInstance(menu, menuComposer);

    viewHierarchy->load(menuComposable, matcherFactory->makeMenuBarTypeMatcher());

    return a.exec();
}