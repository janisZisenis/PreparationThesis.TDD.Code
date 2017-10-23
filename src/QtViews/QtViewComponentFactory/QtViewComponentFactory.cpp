#include "QtViewComponentFactory.h"

#include "QtViews/QMainWindowBased/QtShell/QtShell.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellDecomposingVisitor.h"

#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerPresenter.h>
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorer.h"

#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include <CrossViews/PropertiesExplorerPresenter/PropertiesExplorerPresenter.h>

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarComposingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarDecomposingVisitor.h"

#include "QtViews/QActionBased/QtMenu/QtMenu.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuComposingVisitor.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuDecomposingVisitor.h"

#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>
#include "QtViews/QActionBased/QtAction/QtAction.h"

#include <CodeBase/CBTransAction/CBNullTransAction.h>
#include <CodeBase/CBCommandInvoker/CBCommandInvoker.h>
#include <CodeBase/CBCommandHistory/CBCommandHistory.h>
#include <CodeBaseImp/CBTransActionAppearanceImp/CBTransActionAppearanceImp.h>
#include <CodeBaseImp/CBFixedActionAppearance/CBFixedAppearance.h>
#include <CodeBaseImp/CBFixedActionAppearance/CBFixedAccessibility.h>
#include <CodeBaseImp/CBFixedActionAppearance/CBFixedState.h>
#include <CodeBaseImp/CBFixedActionAppearance/CBFixedTitle.h>

#include <CodeBaseImp/CBTransActions/UndoAction/Action/CBUndoAction.h>
#include <CodeBaseImp/CBTransActions/UndoAction/Accessibility/CBUndoDependentAccessibility.h>

#include <CodeBaseImp/CBTransActions/RedoAction/Action/CBRedoAction.h>
#include <CodeBaseImp/CBTransActions/RedoAction/Accessibility/CBRedoDependentAccessibility.h>

#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/TransActions/RemoveAction/RemoveAction.h>
#include <CrossViews/TransActions/RemoveAction/Appearance/SelectionDependentAccessibility.h>

#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

QtViewComponentFactoryPtr QtViewComponentFactory::getNewInstance() {
    return QtViewComponentFactoryPtr(new QtViewComponentFactory());
}
QtViewComponentFactory::~QtViewComponentFactory() {}
QtViewComponentFactory::QtViewComponentFactory() {}

CNComponentPtr QtViewComponentFactory::makeShellComponent() {
    QtShellPtr shell = QtShell::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(QtShellComposingVisitor::getNewInstance(shell),
                                                  QtShellDecomposingVisitor::getNewInstance(shell));
    return makeComposable(shell, composer);
}
CNComponentPtr QtViewComponentFactory::makeSolutionExplorerComponent(SelectionModelPtr selectionModel) {
    QtSolutionExplorerPtr view = QtSolutionExplorer::getNewInstance();
    SolutionExplorerPresenterPtr presenter = SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makePropertiesExplorerComponent(SelectionModelPtr selectionModel,
                                                                       std::shared_ptr<HierarchicModelAccess> modelAccess) {
    QtPropertiesExplorerPtr view = QtPropertiesExplorer::getNewInstance();
    PropertiesExplorerPresenterPtr presenter = PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}

CNComponentPtr QtViewComponentFactory::makeMenuBarComponent() {
    QtMenuBarPtr menuBar = QtMenuBar::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(QtMenuBarComposingVisitor::getNewInstance(menuBar),
                                                  QtMenuBarDecomposingVisitor::getNewInstance(menuBar));

    return makeComposable(menuBar, composer);
}
CNComponentPtr QtViewComponentFactory::makeMenuComponent(std::string title, std::string tag) {
    QtMenuPtr menu = QtMenu::getNewInstance(title);
    menu->setTag(tag);
    CNComposerPtr composer = makeVisitingComposer(QtMenuComposingVisitor::getNewInstance(menu),
                                                  QtMenuDecomposingVisitor::getNewInstance(menu));

    return makeComposable(menu, composer);
}
CNComponentPtr QtViewComponentFactory::makeUndoActionComponent(CBCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                      makeFixedActionState(OFF),
                                                                      makeFixedActionTitle("Undo"));
    CBTransActionPtr action = CBUndoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRedoActionComponent(CBCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                      makeFixedActionState(OFF),
                                                                      makeFixedActionTitle("Redo"));
    CBTransActionPtr action = CBRedoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRemoveActionComponent(SelectionModelPtr selectionModel,
                                                                 std::shared_ptr<InsertingHierarchicModel> model,
                                                                 CBCommandInvokerPtr invoker) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                      makeFixedActionState(OFF),
                                                                      makeFixedActionTitle("Remove"));
    RemoveActionPtr action = RemoveAction::getNewInstance(selectionModel, model, invoker);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}

CNComponentPtr QtViewComponentFactory::makeHelloWorldMenuComponent(std::string tag) {
    QtMenuPtr menu = QtMenu::getNewInstance("HelloWorld!");
    menu->setTag(tag);
    CNComposerPtr composer = makeVisitingComposer(QtMenuComposingVisitor::getNewInstance(menu),
                                                  QtMenuDecomposingVisitor::getNewInstance(menu));

    return makeComposable(menu, composer);
}
CNComponentPtr QtViewComponentFactory::makeExampleActionComponent() {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeFixedTransActionAppearance(false, OFF, "Example");
    CBNullTransActionPtr action = CBNullTransAction::getNewInstance();
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}

CBTransActionAppearancePtr QtViewComponentFactory::makeFixedTransActionAppearance(bool accessibility, CBActionStates state, std::string title) {
    return CBFixedAppearance::getNewInstance(accessibility, state, title);
}
CBTransActionAppearancePtr QtViewComponentFactory::makeTransActionAppearance(CBActionAccessibilityPtr accessibility,
                                                                             CBActionStatePtr state,
                                                                             CBActionTitlePtr title) {
    return CBTransActionAppearanceImp::getNewInstance(accessibility, state, title);
}

CBActionAccessibilityPtr QtViewComponentFactory::makeFixedActionAcessibility(bool accessibility) {
    return CBFixedAccessibility::getNewInstance(accessibility);
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
CBActionStatePtr QtViewComponentFactory::makeFixedActionState(CBActionStates state) {
    return CBFixedState::getNewInstance(state);
}
CBActionTitlePtr QtViewComponentFactory::makeFixedActionTitle(std::string title) {
    return CBFixedTitle::getNewInstance(title);
}



CNComponentPtr QtViewComponentFactory::makeComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposable::getNewInstance(visitable, composer);
}
CNComposerPtr QtViewComponentFactory::makeVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return CNVisitingComposer::getNewInstance(composing, decomposing);
}
CNComposerPtr QtViewComponentFactory::makeNullComposer() {
    return CNNullComposer::getNewInstance();
}

MenuEntryViewPtr QtViewComponentFactory::makeMenuEntryView() {
    return QtAction::getNewInstance();
}

MenuEntryPresenterPtr QtViewComponentFactory::makeMenuEntryPresenter(MenuEntryViewPtr view,
                                                                                   CBTransActionAppearancePtr appearance,
                                                                                   CBTransActionPtr action) {
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

