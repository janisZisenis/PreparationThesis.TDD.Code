#include <QApplication>

#include <CodeBaseImp/CBCommandStack/CBCommandStack.h>

#include <CrossNative/CNComponent/CNComponent.h>
#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>

#include <CrossViews/SelectionModel/SelectionModelImp.h>
#include <CrossViews/HierarchicModel/HierarchicModel.h>

#include "QtViews/QtViewComponentFactory/QtViewComponentFactory.h"
#include "QtViews/QtViewMatcherFactory/QtViewMatcherFactory.h"

int main(int argc, char** argv) {
    SelectionModelImpPtr selectionModel = SelectionModelImp::getNewInstance();
    HierarchicModelPtr model = HierarchicModel::getNewInstance();
    CBCommandStackPtr commandStack = CBCommandStack::getNewInstance();


    QApplication a(argc, argv);

    QtViewComponentFactoryPtr componentFactory = QtViewComponentFactory::getNewInstance();
    CNComponentPtr shell = componentFactory->makeShellComponent();
    CNComponentPtr menuBar = componentFactory->makeMenuBarComponent();
    CNComponentPtr solutionExplorer = componentFactory->makeSolutionExplorerComponent(selectionModel);
    CNComponentPtr propertiesExplorer = componentFactory->makePropertiesExplorerComponent(selectionModel, model);
    CNComponentPtr editMenu = componentFactory->makeMenuComponent("Edit", "edit-menu");
    CNComponentPtr addMenu = componentFactory->makeMenuComponent("Add", "add-menu");
    CNComponentPtr undoMenuEntry = componentFactory->makeUndoActionComponent(commandStack);
    CNComponentPtr redoMenuEntry = componentFactory->makeRedoActionComponent(commandStack);
    CNComponentPtr removeMenuEntry = componentFactory->makeRemoveActionComponent(selectionModel, model, commandStack);
    CNComponentPtr stlMenuEntry;
    CNComponentPtr gridGeneratorMenuEntry;

    QtViewMatcherFactoryPtr matcherFactory = QtViewMatcherFactory::getNewInstance();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(shell, matcherFactory->makeTopLevelMatcher());
    viewHierarchy->load(solutionExplorer, matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(propertiesExplorer, matcherFactory->makeShellTypeMatcher());
    viewHierarchy->load(menuBar, matcherFactory->makeShellTypeMatcher());

    viewHierarchy->load(editMenu, matcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(addMenu, matcherFactory->makeMenuBarTypeMatcher());
    viewHierarchy->load(undoMenuEntry, matcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(redoMenuEntry, matcherFactory->makeTagMatcher("edit-menu"));
    viewHierarchy->load(removeMenuEntry, matcherFactory->makeTagMatcher("edit-menu"));

    return a.exec();
}