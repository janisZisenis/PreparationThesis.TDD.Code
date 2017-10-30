#include "QtViewComponentFactory.h"

#include <Base/CNActionAppearanceFactory/CNActionAppearanceFactory.h>
#include <Base/CBTransActionAppearance/CNTransActionAppearance.h>
#include <Base/CBTransActionAppearance/CNActionTitle.h>
#include <Hierarchies/CNComponentFactory/CNComponentFactory.h>
#include <Hierarchies/CNComposerFactory/CNComposerFactory.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <Hierarchies/CNComposer/CNComposer.h>

#include "QtViews/QMainWindowBased/QtShell/QtShell.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellDecomposingVisitor.h"

#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerPresenter.h>
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorer.h"

#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include <CrossViews/HierarchicModel/API/HierarchicModelAccess.h>
#include <CrossViews/PropertiesExplorerPresenter/PropertiesExplorerPresenter.h>

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarComposingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarDecomposingVisitor.h"

#include <CrossViews/DynamicMenuPresenter/DynamicMenuPresenter.h>
#include "QtViews/QActionBased/QtMenu/QtMenu.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuComposingVisitor.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuDecomposingVisitor.h"

#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>
#include "QtViews/QActionBased/QtAction/QtAction.h"

#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Base/CNCommandHistory/CNCommandHistory.h>

#include <Base/TransActions/CNUndoAction/Action/CNUndoAction.h>
#include <Base/TransActions/CNUndoAction/Accessibility/CNUndoDependentAccessibility.h>

#include <Base/TransActions/CNRedoAction/Action/CNRedoAction.h>
#include <Base/TransActions/CNRedoAction/Accessibility/CNRedoDependentAccessibility.h>

#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/TransActions/RemoveAction/RemoveAction.h>
#include <CrossViews/TransActions/RemoveAction/Appearance/SelectionDependentAccessibility.h>

QtViewComponentFactoryPtr QtViewComponentFactory::getNewInstance() {
    return QtViewComponentFactoryPtr(new QtViewComponentFactory());
}
QtViewComponentFactory::~QtViewComponentFactory() {}
QtViewComponentFactory::QtViewComponentFactory()
        : appearanceFactory(CNActionAppearanceFactory::getNewInstance()),
          componentFactory(CNComponentFactory::getNewInstance()),
          composerFactory(CNComposerFactory::getNewInstance()) {}

CNComponentPtr QtViewComponentFactory::makeShellComponent() {
    QtShellPtr shell = QtShell::getNewInstance();
    CNComposerPtr composer = makeCNVisitingComposer(QtShellComposingVisitor::getNewInstance(shell),
                                                    QtShellDecomposingVisitor::getNewInstance(shell));
    return makeCNComposable(shell, composer);
}
CNComponentPtr QtViewComponentFactory::makeSolutionExplorerComponent(SelectionModelPtr selectionModel,
                                                                     HierarchicModelAccessPtr modelAccess,
                                                                     std::shared_ptr<QtSolutionItemFactory> itemFactory) {
    QtSolutionExplorerPtr view = QtSolutionExplorer::getNewInstance(itemFactory);
    SolutionExplorerPresenterPtr presenter = SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    view->setListener(presenter);
    modelAccess->addListener(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makePropertiesExplorerComponent(SelectionModelPtr selectionModel,
                                                                       HierarchicModelAccessPtr modelAccess,
                                                                       std::shared_ptr<QtPropertiesModelFactory> modelFactory) {
    QtPropertiesExplorerPtr view = QtPropertiesExplorer::getNewInstance(modelFactory);
    PropertiesExplorerPresenterPtr presenter = PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CNComponentPtr QtViewComponentFactory::makeMenuBarComponent() {
    QtMenuBarPtr menuBar = QtMenuBar::getNewInstance();
    CNComposerPtr composer = makeCNVisitingComposer(QtMenuBarComposingVisitor::getNewInstance(menuBar),
                                                    QtMenuBarDecomposingVisitor::getNewInstance(menuBar));

    return makeCNComposable(menuBar, composer);
}
CNComponentPtr QtViewComponentFactory::makeMenuComponent(std::string title, std::string tag) {
    QtMenuPtr view = makeQtMenu(title, tag);
    CNComposerPtr composer = makeCNVisitingComposer(QtMenuComposingVisitor::getNewInstance(view),
                                                    QtMenuDecomposingVisitor::getNewInstance(view));

    return makeCNComposable(view, composer);
}
CNComponentPtr QtViewComponentFactory::makeUndoActionComponent(CNCommandHistoryPtr commandHistory) {
    QtActionPtr view = makeQtAction();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Undo"));
    CNTransActionPtr action = CNUndoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRedoActionComponent(CNCommandHistoryPtr commandHistory) {
    QtActionPtr view = makeQtAction();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Redo"));
    CNTransActionPtr action = CNRedoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRemoveActionComponent(SelectionModelPtr selectionModel,
                                                                 std::shared_ptr<InsertingHierarchicModel> model,
                                                                 CNCommandInvokerPtr invoker) {
    QtActionPtr view = makeQtAction();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Remove"));
    RemoveActionPtr action = RemoveAction::getNewInstance(selectionModel, model, invoker);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CNTransActionAppearancePtr QtViewComponentFactory::makeCBTransActionAppearance(CNActionAccessibilityPtr accessibility,
                                                                               CNActionStatePtr state,
                                                                               CNActionTitlePtr title) {
    return appearanceFactory->makeCNTransActionAppearance(accessibility, state, title);
}
CNTransActionAppearancePtr QtViewComponentFactory::makeCBFixedTransActionAppearance(bool accessibility, CNActionStates state, std::string title) {
    return appearanceFactory->makeCNFixedTransActionAppearance(accessibility, state, title);
}

CNActionStatePtr QtViewComponentFactory::makeCBFixedActionState(CNActionStates state) {
    return appearanceFactory->makeCNFixedActionState(state);
}
CNActionTitlePtr QtViewComponentFactory::makeCBFixedActionTitle(std::string title) {
    return appearanceFactory->makeCNFixedActionTitle(title);
}

CNActionAccessibilityPtr QtViewComponentFactory::makeUndoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNUndoDependentAccessibility::getNewInstance(commandHistory);
}
CNActionAccessibilityPtr QtViewComponentFactory::makeRedoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNRedoDependentAccessibility::getNewInstance(commandHistory);
}
CNActionAccessibilityPtr QtViewComponentFactory::makeSelectionDependenAccessibility(SelectionModelPtr selectionModel) {
    return SelectionDependentAccessibility::getNewInstance(selectionModel);
}



CNComponentPtr QtViewComponentFactory::makeCNComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return componentFactory->makeCNComposable(visitable, composer);
}
CNComposerPtr QtViewComponentFactory::makeCNVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return composerFactory->makeCNVisitingComposer(composing, decomposing);
}
CNComposerPtr QtViewComponentFactory::makeCNNullComposer() {
    return composerFactory->makeCNNullComposer();
}

QtMenuPtr QtViewComponentFactory::makeQtMenu(std::string title, std::string tag) {
    QtMenuPtr menu = QtMenu::getNewInstance(title);
    menu->setTag(tag);
    return menu;
}

QtActionPtr QtViewComponentFactory::makeQtAction() {
    return QtAction::getNewInstance();
}

MenuEntryPresenterPtr QtViewComponentFactory::makeMenuEntryPresenter(MenuEntryViewPtr view,
                                                                     CNTransActionAppearancePtr appearance,
                                                                     CNTransActionPtr action) {
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

DynamicMenuPresenterPtr QtViewComponentFactory::makeDynamicMenuPresenter(MenuViewPtr view,
                                                                std::shared_ptr<CNComposer> composer,
                                                                std::shared_ptr<MenuEntryListProvider> listProvider) {
    return DynamicMenuPresenter::getNewInstance(view, composer, listProvider);
}
