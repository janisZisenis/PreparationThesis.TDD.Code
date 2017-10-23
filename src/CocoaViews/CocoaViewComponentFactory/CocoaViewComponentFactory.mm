#include "CocoaViewComponentFactory.h"

#include "CocoaViews/NSWindowBased/CocoaShell/CocoaShell.h"
#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellComposingVisitor.h"
#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellDecomposingVisitor.h"

#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerPresenter.h>
#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorer.h"

#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"
#include <CrossViews/HierarchicModel/API/HierarchicModelAccess.h>
#include <CrossViews/PropertiesExplorerPresenter/PropertiesExplorerPresenter.h>

#include "CocoaViews/NSMenuBased/CocoaMenuBar/CocoaMenuBar.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarDecomposingVisitor.h"

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h"

#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"

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

CocoaViewComponentFactoryPtr CocoaViewComponentFactory::getNewInstance() {
    return CocoaViewComponentFactoryPtr(new CocoaViewComponentFactory());
}
CocoaViewComponentFactory::~CocoaViewComponentFactory() {}
CocoaViewComponentFactory::CocoaViewComponentFactory() {}

CNComponentPtr CocoaViewComponentFactory::makeShellComponent() {
    CocoaShellPtr shell = CocoaShell::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(CocoaShellComposingVisitor::getNewInstance(shell),
                                                  CocoaShellDecomposingVisitor::getNewInstance(shell));
    return makeComposable(shell, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeSolutionExplorerComponent(SelectionModelPtr selectionModel,
                                                                     HierarchicModelAccessPtr modelAccess,
                                                                     std::shared_ptr<CocoaSolutionItemFactory> itemFactory) {
    CocoaSolutionExplorerPtr view = CocoaSolutionExplorer::getNewInstance(itemFactory);
    SolutionExplorerPresenterPtr presenter = SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    view->setListener(presenter);
    modelAccess->addListener(presenter);
    CNComposerPtr composer = makeNullComposer();

    return makeComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makePropertiesExplorerComponent(SelectionModelPtr selectionModel,
                                                                          HierarchicModelAccessPtr modelAccess,
                                                                          std::shared_ptr<CocoaPropertiesModelFactory> modelFactory) {
    CocoaPropertiesExplorerPtr view = CocoaPropertiesExplorer::getNewInstance(modelFactory);
    PropertiesExplorerPresenterPtr presenter = PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeNullComposer();

    return makeComposable(presenter, composer);
}

CNComponentPtr CocoaViewComponentFactory::makeMenuBarComponent() {
    CocoaMenuBarPtr menuBar = CocoaMenuBar::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(CocoaMenuBarComposingVisitor::getNewInstance(menuBar),
                                                  CocoaMenuBarDecomposingVisitor::getNewInstance(menuBar));

    return makeComposable(menuBar, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeMenuComponent(std::string title, std::string tag) {
    CocoaMenuPtr menu = CocoaMenu::getNewInstance(title);
    menu->setTag(tag);
    CNComposerPtr composer = makeVisitingComposer(CocoaMenuComposingVisitor::getNewInstance(menu),
                                                  CocoaMenuDecomposingVisitor::getNewInstance(menu));

    return makeComposable(menu, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeUndoActionComponent(CBCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                      makeFixedActionState(OFF),
                                                                      makeFixedActionTitle("Undo"));
    CBTransActionPtr action = CBUndoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeNullComposer();

    return makeComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRedoActionComponent(CBCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                      makeFixedActionState(OFF),
                                                                      makeFixedActionTitle("Redo"));
    CBTransActionPtr action = CBRedoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeNullComposer();

    return makeComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRemoveActionComponent(SelectionModelPtr selectionModel,
                                                                 std::shared_ptr<InsertingHierarchicModel> model,
                                                                 CBCommandInvokerPtr invoker) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                      makeFixedActionState(OFF),
                                                                      makeFixedActionTitle("Remove"));
    RemoveActionPtr action = RemoveAction::getNewInstance(selectionModel, model, invoker);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeNullComposer();

    return makeComposable(presenter, composer);
}

CBTransActionAppearancePtr CocoaViewComponentFactory::makeFixedTransActionAppearance(bool accessibility, CBActionStates state, std::string title) {
    return CBFixedAppearance::getNewInstance(accessibility, state, title);
}
CBTransActionAppearancePtr CocoaViewComponentFactory::makeTransActionAppearance(CBActionAccessibilityPtr accessibility,
                                                                             CBActionStatePtr state,
                                                                             CBActionTitlePtr title) {
    return CBTransActionAppearanceImp::getNewInstance(accessibility, state, title);
}

CBActionAccessibilityPtr CocoaViewComponentFactory::makeFixedActionAcessibility(bool accessibility) {
    return CBFixedAccessibility::getNewInstance(accessibility);
}
CBActionAccessibilityPtr CocoaViewComponentFactory::makeUndoDependenAccessibility(CBCommandHistoryPtr commandHistory) {
    return CBUndoDependentAccessibility::getNewInstance(commandHistory);
}
CBActionAccessibilityPtr CocoaViewComponentFactory::makeRedoDependenAccessibility(CBCommandHistoryPtr commandHistory) {
    return CBRedoDependentAccessibility::getNewInstance(commandHistory);
}
CBActionAccessibilityPtr CocoaViewComponentFactory::makeSelectionDependenAccessibility(SelectionModelPtr selectionModel) {
    return SelectionDependentAccessibility::getNewInstance(selectionModel);
}
CBActionStatePtr CocoaViewComponentFactory::makeFixedActionState(CBActionStates state) {
    return CBFixedState::getNewInstance(state);
}
CBActionTitlePtr CocoaViewComponentFactory::makeFixedActionTitle(std::string title) {
    return CBFixedTitle::getNewInstance(title);
}



CNComponentPtr CocoaViewComponentFactory::makeComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposable::getNewInstance(visitable, composer);
}
CNComposerPtr CocoaViewComponentFactory::makeVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return CNVisitingComposer::getNewInstance(composing, decomposing);
}
CNComposerPtr CocoaViewComponentFactory::makeNullComposer() {
    return CNNullComposer::getNewInstance();
}

MenuEntryViewPtr CocoaViewComponentFactory::makeMenuEntryView() {
    return CocoaMenuItem::getNewInstance();
}

MenuEntryPresenterPtr CocoaViewComponentFactory::makeMenuEntryPresenter(MenuEntryViewPtr view,
                                                                     CBTransActionAppearancePtr appearance,
                                                                     CBTransActionPtr action) {
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

