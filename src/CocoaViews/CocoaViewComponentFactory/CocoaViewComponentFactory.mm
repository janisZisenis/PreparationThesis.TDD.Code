#include "CocoaViewComponentFactory.h"

#include <Base/CNActionAppearanceFactory/CNActionAppearanceFactory.h>
#include <Base/CNTransActionAppearance/CNTransActionAppearance.h>
#include <Base/CNTransActionAppearance/CNTransActionTitle.h>
#include <Hierarchies/CNComponentFactory/CNComponentFactory.h>
#include <Hierarchies/CNComposerFactory/CNComposerFactory.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <Hierarchies/CNComposer/CNComposer.h>

#include "CocoaViews/NSWindowBased/CocoaShell/CocoaShell.h"
#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellComposingVisitor.h"
#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellDecomposingVisitor.h"

#include <CrossViews/CNSolutionExplorerPresenter/CNSolutionExplorerPresenter.h>
#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorer.h"

#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"
#include <CrossViews/CNHierarchicModel/API/CNHierarchicComponentAccess.h>
#include <CrossViews/CNPropertiesExplorerPresenter/CNPropertiesExplorerPresenter.h>

#include "CocoaViews/NSMenuBased/CocoaMenuBar/CocoaMenuBar.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarDecomposingVisitor.h"

#include <CrossViews/CNDynamicMenuPresenter/CNDynamicMenuPresenter.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h"

#include <CrossViews/CNMenuEntryPresenter/CNMenuEntryPresenter.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"

#include <Base/CNTransAction/CNNullTransAction.h>
#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Base/CNCommandHistory/CNCommandHistory.h>

#include <Base/TransActions/CNUndoAction/Action/CNUndoAction.h>
#include <Base/TransActions/CNUndoAction/Accessibility/CNUndoDependentAccessibility.h>

#include <Base/TransActions/CNRedoAction/Action/CNRedoAction.h>
#include <Base/TransActions/CNRedoAction/Accessibility/CNRedoDependentAccessibility.h>

#include <CrossViews/CNSelectionModel/CNSelectionModel.h>
#include <CrossViews/TransActions/CNRemoveAction/CNRemoveAction.h>
#include <CrossViews/TransActions/CNRemoveAction/Appearance/CNSelectionDependentAccessibility.h>

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
CNComponentPtr CocoaViewComponentFactory::makeSolutionExplorerComponent(CNSelectionModelPtr selectionModel,
                                                                        CNHierarchicComponentAccessPtr modelAccess,
                                                                        std::shared_ptr<CocoaSolutionItemFactory> itemFactory) {
    CocoaSolutionExplorerPtr view = CocoaSolutionExplorer::getNewInstance(itemFactory);
    CNSolutionExplorerPresenterPtr presenter = CNSolutionExplorerPresenter::getNewInstance(view, selectionModel);
    view->setListener(presenter);
    modelAccess->addListener(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makePropertiesExplorerComponent(CNSelectionModelPtr selectionModel,
                                                                          CNHierarchicComponentAccessPtr modelAccess,
                                                                          std::shared_ptr<CocoaPropertiesModelFactory> modelFactory) {
    CocoaPropertiesExplorerPtr view = CocoaPropertiesExplorer::getNewInstance(modelFactory);
    CNPropertiesExplorerPresenterPtr presenter = CNPropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
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
    CNMenuEntryViewPtr view = makeMenuEntryView();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeUndoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Undo"));
    CNTransActionPtr action = CNUndoAction::getNewInstance(commandHistory);
    CNMenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRedoActionComponent(CNCommandHistoryPtr commandHistory) {
    CNMenuEntryViewPtr view = makeMenuEntryView();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeRedoDependenAccessibility(commandHistory),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Redo"));
    CNTransActionPtr action = CNRedoAction::getNewInstance(commandHistory);
    CNMenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr CocoaViewComponentFactory::makeRemoveActionComponent(CNSelectionModelPtr selectionModel,
                                                                    std::shared_ptr<CNComponentInserter> model,
                                                                    CNCommandInvokerPtr invoker) {
    CNMenuEntryViewPtr view = makeMenuEntryView();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Remove"));
    CNRemoveActionPtr action = CNRemoveAction::getNewInstance(selectionModel, model, invoker);
    CNMenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CNTransActionAppearancePtr CocoaViewComponentFactory::makeCBFixedTransActionAppearance(bool accessibility,
                                                                                       CNTransActionStateValues state,
                                                                                       std::string title) {
    return appearanceFactory->makeCNFixedTransActionAppearance(accessibility, state, title);
}
CNTransActionAppearancePtr CocoaViewComponentFactory::makeCBTransActionAppearance(CNTransActionAccessibilityPtr accessibility,
                                                                                  CNTransActionStatePtr state,
                                                                                  CNTransActionTitlePtr title) {
    return appearanceFactory->makeCNTransActionAppearance(accessibility, state, title);
}

CNTransActionStatePtr CocoaViewComponentFactory::makeCBFixedActionState(CNTransActionStateValues state) {
    return appearanceFactory->makeCNFixedActionState(state);
}
CNTransActionTitlePtr CocoaViewComponentFactory::makeCBFixedActionTitle(std::string title) {
    return appearanceFactory->makeCNFixedActionTitle(title);
}

CNTransActionAccessibilityPtr CocoaViewComponentFactory::makeUndoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNUndoDependentAccessibility::getNewInstance(commandHistory);
}
CNTransActionAccessibilityPtr CocoaViewComponentFactory::makeRedoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNRedoDependentAccessibility::getNewInstance(commandHistory);
}
CNTransActionAccessibilityPtr CocoaViewComponentFactory::makeSelectionDependenAccessibility(CNSelectionModelPtr selectionModel) {
    return CNSelectionDependentAccessibility::getNewInstance(selectionModel);
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

CNMenuEntryViewPtr CocoaViewComponentFactory::makeMenuEntryView() {
    return CocoaMenuItem::getNewInstance();
}

CNMenuEntryPresenterPtr CocoaViewComponentFactory::makeMenuEntryPresenter(CNMenuEntryViewPtr view,
                                                                          CNTransActionAppearancePtr appearance,
                                                                          CNTransActionPtr action) {
    CNMenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

CNDynamicMenuPresenterPtr CocoaViewComponentFactory::makeDynamicMenuPresenter(CNMenuViewPtr view,
                                                                              std::shared_ptr<CNComposer> composer,
                                                                              std::shared_ptr<CNComponentListProvider> listProvider) {
    return CNDynamicMenuPresenter::getNewInstance(view, composer, listProvider);
}