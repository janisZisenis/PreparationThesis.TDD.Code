#include "CocoaViewComponentFactory.h"

#include <Base/CNActionAppearanceFactory/CNActionAppearanceFactory.h>
#include <Base/CBTransActionAppearance/CNTransActionAppearance.h>
#include <Base/CBTransActionAppearance/CNActionTitle.h>
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

#include <Base/CNTransAction/CNNullTransAction.h>
#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Base/CNCommandHistory/CNCommandHistory.h>

#include <Base/TransActions/CNUndoAction/Action/CNUndoAction.h>
#include <Base/TransActions/CNUndoAction/Accessibility/CNUndoDependentAccessibility.h>

#include <Base/TransActions/CNRedoAction/Action/CNRedoAction.h>
#include <Base/TransActions/CNRedoAction/Accessibility/CNRedoDependentAccessibility.h>

#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/TransActions/RemoveAction/RemoveAction.h>
#include <CrossViews/TransActions/RemoveAction/Appearance/SelectionDependentAccessibility.h>

CocoaViewComponentFactoryPtr CocoaViewComponentFactory::getNewInstance() {
    return CocoaViewComponentFactoryPtr(new CocoaViewComponentFactory());
}
CocoaViewComponentFactory::~CocoaViewComponentFactory() {}
CocoaViewComponentFactory::CocoaViewComponentFactory()
        : appearanceFactory(CNActionAppearanceFactory::getNewInstance()),
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
CNComponentPtr CocoaViewComponentFactory::makeUndoActionComponent(CNCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Undo"));
    CNTransActionPtr action = CNUndoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRedoActionComponent(CNCommandHistoryPtr commandHistory) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Redo"));
    CNTransActionPtr action = CNRedoAction::getNewInstance(commandHistory);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRemoveActionComponent(SelectionModelPtr selectionModel,
                                                                 std::shared_ptr<InsertingHierarchicModel> model,
                                                                 CNCommandInvokerPtr invoker) {
    MenuEntryViewPtr view = makeMenuEntryView();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Remove"));
    RemoveActionPtr action = RemoveAction::getNewInstance(selectionModel, model, invoker);
    MenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CNTransActionAppearancePtr CocoaViewComponentFactory::makeCBFixedTransActionAppearance(bool accessibility,
                                                                                       CNActionStates state,
                                                                                       std::string title) {
    return appearanceFactory->makeCNFixedTransActionAppearance(accessibility, state, title);
}
CNTransActionAppearancePtr CocoaViewComponentFactory::makeCBTransActionAppearance(CNActionAccessibilityPtr accessibility,
                                                                                  CNActionStatePtr state,
                                                                                  CNActionTitlePtr title) {
    return appearanceFactory->makeCNTransActionAppearance(accessibility, state, title);
}

CNActionStatePtr CocoaViewComponentFactory::makeCBFixedActionState(CNActionStates state) {
    return appearanceFactory->makeCNFixedActionState(state);
}
CNActionTitlePtr CocoaViewComponentFactory::makeCBFixedActionTitle(std::string title) {
    return appearanceFactory->makeCNFixedActionTitle(title);
}

CNActionAccessibilityPtr CocoaViewComponentFactory::makeUndoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNUndoDependentAccessibility::getNewInstance(commandHistory);
}
CNActionAccessibilityPtr CocoaViewComponentFactory::makeRedoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNRedoDependentAccessibility::getNewInstance(commandHistory);
}
CNActionAccessibilityPtr CocoaViewComponentFactory::makeSelectionDependenAccessibility(SelectionModelPtr selectionModel) {
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
                                                                        CNTransActionAppearancePtr appearance,
                                                                        CNTransActionPtr action) {
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

DynamicMenuPresenterPtr CocoaViewComponentFactory::makeDynamicMenuPresenter(MenuViewPtr view,
                                                                         std::shared_ptr<CNComposer> composer,
                                                                         std::shared_ptr<MenuEntryListProvider> listProvider) {
    return DynamicMenuPresenter::getNewInstance(view, composer, listProvider);
}