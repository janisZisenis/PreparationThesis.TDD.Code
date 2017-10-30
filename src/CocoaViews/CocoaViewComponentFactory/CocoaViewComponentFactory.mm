#include "CocoaViewComponentFactory.h"

#include <CodeBaseImp/CBActionAppearanceFactory/CBActionAppearanceFactory.h>
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearance.h>
#include <CodeBase/CBTransActionAppearance/CBActionTitle.h>
#include <Hierarchies/CNComponentFactory/CNComponentFactory.h>
#include <Hierarchies/CNComposerFactory/CNComposerFactory.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <Hierarchies/CNComposer/CNComposer.h>

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

#include <CrossViews/DynamicMenuPresenter/DynamicMenuPresenter.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h"

#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"

#include <CodeBase/CBTransAction/CBNullTransAction.h>
#include <CodeBase/CBCommandInvoker/CBCommandInvoker.h>
#include <CodeBase/CBCommandHistory/CBCommandHistory.h>

#include <CodeBaseImp/CBTransActions/UndoAction/Action/CBUndoAction.h>
#include <CodeBaseImp/CBTransActions/UndoAction/Accessibility/CBUndoDependentAccessibility.h>

#include <CodeBaseImp/CBTransActions/RedoAction/Action/CBRedoAction.h>
#include <CodeBaseImp/CBTransActions/RedoAction/Accessibility/CBRedoDependentAccessibility.h>

#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/TransActions/RemoveAction/RemoveAction.h>
#include <CrossViews/TransActions/RemoveAction/Appearance/SelectionDependentAccessibility.h>

CocoaViewComponentFactoryPtr CocoaViewComponentFactory::getNewInstance() {
    return CocoaViewComponentFactoryPtr(new CocoaViewComponentFactory());
}
CocoaViewComponentFactory::~CocoaViewComponentFactory() {}
CocoaViewComponentFactory::CocoaViewComponentFactory()
        : appearanceFactory(CBActionAppearanceFactory::getNewInstance()),
          componentFactory(CNComponentFactory::getNewInstance()),
          composerFactory(CNComposerFactory::getNewInstance()) {}

CNComponentPtr CocoaViewComponentFactory::makeShellComponent() {
    CocoaShellPtr shell = CocoaShell::getNewInstance();
    CNComposerPtr composer = makeCNVisitingComposer(CocoaShellComposingVisitor::getNewInstance(shell),
                                                    CocoaShellDecomposingVisitor::getNewInstance(shell));
    return makeCNComposable(shell, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeSolutionExplorerComponent(SelectionModelPtr selectionModel,
                                                                     HierarchicModelAccessPtr modelAccess,
                                                                     std::shared_ptr<CocoaSolutionItemFactory> itemFactory) {
    CocoaSolutionExplorerPtr view = CocoaSolutionExplorer::getNewInstance(itemFactory);
    SolutionExplorerPresenterPtr presenter = SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    view->setListener(presenter);
    modelAccess->addListener(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makePropertiesExplorerComponent(SelectionModelPtr selectionModel,
                                                                          HierarchicModelAccessPtr modelAccess,
                                                                          std::shared_ptr<CocoaPropertiesModelFactory> modelFactory) {
    CocoaPropertiesExplorerPtr view = CocoaPropertiesExplorer::getNewInstance(modelFactory);
    PropertiesExplorerPresenterPtr presenter = PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CNComponentPtr CocoaViewComponentFactory::makeMenuBarComponent() {
    CocoaMenuBarPtr menuBar = CocoaMenuBar::getNewInstance();
    CNComposerPtr composer = makeCNVisitingComposer(CocoaMenuBarComposingVisitor::getNewInstance(menuBar),
                                                    CocoaMenuBarDecomposingVisitor::getNewInstance(menuBar));

    return makeCNComposable(menuBar, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeMenuComponent(std::string title, std::string tag) {
    CocoaMenuPtr menu = CocoaMenu::getNewInstance(title);
    menu->setTag(tag);
    CNComposerPtr composer = makeCNVisitingComposer(CocoaMenuComposingVisitor::getNewInstance(menu),
                                                    CocoaMenuDecomposingVisitor::getNewInstance(menu));

    return makeCNComposable(menu, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeUndoActionComponent(CBCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Undo"));
    CBTransActionPtr action = CBUndoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRedoActionComponent(CBCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Redo"));
    CBTransActionPtr action = CBRedoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRemoveActionComponent(SelectionModelPtr selectionModel,
                                                                 std::shared_ptr<InsertingHierarchicModel> model,
                                                                 CBCommandInvokerPtr invoker) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Remove"));
    RemoveActionPtr action = RemoveAction::getNewInstance(selectionModel, model, invoker);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CBTransActionAppearancePtr CocoaViewComponentFactory::makeCBFixedTransActionAppearance(bool accessibility,
                                                                                       CBActionStates state,
                                                                                       std::string title) {
    return appearanceFactory->makeCBFixedTransActionAppearance(accessibility, state, title);
}
CBTransActionAppearancePtr CocoaViewComponentFactory::makeCBTransActionAppearance(CBActionAccessibilityPtr accessibility,
                                                                                  CBActionStatePtr state,
                                                                                  CBActionTitlePtr title) {
    return appearanceFactory->makeCBTransActionAppearance(accessibility, state, title);
}

CBActionStatePtr CocoaViewComponentFactory::makeCBFixedActionState(CBActionStates state) {
    return appearanceFactory->makeCBFixedActionState(state);
}
CBActionTitlePtr CocoaViewComponentFactory::makeCBFixedActionTitle(std::string title) {
    return appearanceFactory->makeCBFixedActionTitle(title);
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

CNComponentPtr CocoaViewComponentFactory::makeCNComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return componentFactory->makeCNComposable(visitable, composer);
}
CNComposerPtr CocoaViewComponentFactory::makeCNVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return composerFactory->makeCNVisitingComposer(composing, decomposing);
}
CNComposerPtr CocoaViewComponentFactory::makeCNNullComposer() {
    return composerFactory->makeCNNullComposer();
}

CocoaMenuPtr CocoaViewComponentFactory::makeCocoaMenu(std::string title, std::string tag) {
    CocoaMenuPtr menu = CocoaMenu::getNewInstance(title);
    menu->setTag(tag);
    return menu;
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

DynamicMenuPresenterPtr CocoaViewComponentFactory::makeDynamicMenuPresenter(MenuViewPtr view,
                                                                         std::shared_ptr<CNComposer> composer,
                                                                         std::shared_ptr<MenuEntryListProvider> listProvider) {
    return DynamicMenuPresenter::getNewInstance(view, composer, listProvider);
}