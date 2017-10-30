#include "QtViewComponentFactory.h"

#include <CodeBaseImp/CBActionAppearanceFactory/CBActionAppearanceFactory.h>
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearance.h>
#include <CodeBase/CBTransActionAppearance/CBActionTitle.h>
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

#include <CodeBase/CBCommandInvoker/CBCommandInvoker.h>
#include <CodeBase/CBCommandHistory/CBCommandHistory.h>

#include <CodeBaseImp/CBTransActions/UndoAction/Action/CBUndoAction.h>
#include <CodeBaseImp/CBTransActions/UndoAction/Accessibility/CBUndoDependentAccessibility.h>

#include <CodeBaseImp/CBTransActions/RedoAction/Action/CBRedoAction.h>
#include <CodeBaseImp/CBTransActions/RedoAction/Accessibility/CBRedoDependentAccessibility.h>

#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/TransActions/RemoveAction/RemoveAction.h>
#include <CrossViews/TransActions/RemoveAction/Appearance/SelectionDependentAccessibility.h>

QtViewComponentFactoryPtr QtViewComponentFactory::getNewInstance() {
    return QtViewComponentFactoryPtr(new QtViewComponentFactory());
}
QtViewComponentFactory::~QtViewComponentFactory() {}
QtViewComponentFactory::QtViewComponentFactory()
        : appearanceFactory(CBActionAppearanceFactory::getNewInstance()),
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
CNComponentPtr QtViewComponentFactory::makeUndoActionComponent(CBCommandHistoryPtr commandHistory) {
    QtActionPtr view = makeQtAction();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Undo"));
    CBTransActionPtr action = CBUndoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRedoActionComponent(CBCommandHistoryPtr commandHistory) {
    QtActionPtr view = makeQtAction();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Redo"));
    CBTransActionPtr action = CBRedoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRemoveActionComponent(SelectionModelPtr selectionModel,
                                                                 std::shared_ptr<InsertingHierarchicModel> model,
                                                                 CBCommandInvokerPtr invoker) {
    QtActionPtr view = makeQtAction();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Remove"));
    RemoveActionPtr action = RemoveAction::getNewInstance(selectionModel, model, invoker);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CBTransActionAppearancePtr QtViewComponentFactory::makeCBTransActionAppearance(CBActionAccessibilityPtr accessibility,
                                                                               CBActionStatePtr state,
                                                                               CBActionTitlePtr title) {
    return appearanceFactory->makeCBTransActionAppearance(accessibility, state, title);
}
CBTransActionAppearancePtr QtViewComponentFactory::makeCBFixedTransActionAppearance(bool accessibility, CBActionStates state, std::string title) {
    return appearanceFactory->makeCBFixedTransActionAppearance(accessibility, state, title);
}

CBActionStatePtr QtViewComponentFactory::makeCBFixedActionState(CBActionStates state) {
    return appearanceFactory->makeCBFixedActionState(state);
}
CBActionTitlePtr QtViewComponentFactory::makeCBFixedActionTitle(std::string title) {
    return appearanceFactory->makeCBFixedActionTitle(title);
}

CBActionAccessibilityPtr QtViewComponentFactory::makeUndoDependenAccessibility(CBCommandHistoryPtr commandHistory) {
    return CBUndoDependentAccessibility::getNewInstance(commandHistory);
}
CBActionAccessibilityPtr QtViewComponentFactory::makeRedoDependenAccessibility(CBCommandHistoryPtr commandHistory) {
    return CBRedoDependentAccessibility::getNewInstance(commandHistory);
}
CBActionAccessibilityPtr QtViewComponentFactory::makeSelectionDependenAccessibility(SelectionModelPtr selectionModel) {
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
                                                                     CBTransActionAppearancePtr appearance,
                                                                     CBTransActionPtr action) {
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

DynamicMenuPresenterPtr QtViewComponentFactory::makeDynamicMenuPresenter(MenuViewPtr view,
                                                                std::shared_ptr<CNComposer> composer,
                                                                std::shared_ptr<MenuEntryListProvider> listProvider) {
    return DynamicMenuPresenter::getNewInstance(view, composer, listProvider);
}
