#include "QtViewComponentFactory.h"

#include <Base/CNActionAppearanceFactory/CNActionAppearanceFactory.h>
#include <Base/CNTransActionAppearance/CNTransActionAppearance.h>
#include <Base/CNTransActionAppearance/CNTransActionTitle.h>
#include <Hierarchies/CNComponentFactory/CNComponentFactory.h>
#include <Hierarchies/CNComposerFactory/CNComposerFactory.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <Hierarchies/CNComposer/CNComposer.h>

#include "QtViews/QMainWindowBased/QtShell/QtShell.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellDecomposingVisitor.h"

#include <CrossViews/CNSolutionExplorerPresenter/CNSolutionExplorerPresenter.h>
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorer.h"

#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include <CrossViews/CNHierarchicModel/API/CNHierarchicComponentAccess.h>
#include <CrossViews/CNPropertiesExplorerPresenter/CNPropertiesExplorerPresenter.h>

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarComposingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarDecomposingVisitor.h"

#include <CrossViews/CNDynamicMenuPresenter/CNDynamicMenuPresenter.h>
#include "QtViews/QActionBased/QtMenu/QtMenu.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuComposingVisitor.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuDecomposingVisitor.h"

#include <CrossViews/CNMenuEntryPresenter/CNMenuEntryPresenter.h>
#include "QtViews/QActionBased/QtAction/QtAction.h"

#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Base/CNCommandHistory/CNCommandHistory.h>

#include <Base/TransActions/CNUndoAction/Action/CNUndoAction.h>
#include <Base/TransActions/CNUndoAction/Accessibility/CNUndoDependentAccessibility.h>

#include <Base/TransActions/CNRedoAction/Action/CNRedoAction.h>
#include <Base/TransActions/CNRedoAction/Accessibility/CNRedoDependentAccessibility.h>

#include <CrossViews/CNSelectionModel/CNSelectionModel.h>
#include <CrossViews/TransActions/CNRemoveAction/CNRemoveAction.h>
#include <CrossViews/TransActions/CNRemoveAction/Appearance/CNSelectionDependentAccessibility.h>

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
CNComponentPtr QtViewComponentFactory::makeSolutionExplorerComponent(CNSelectionModelPtr selectionModel,
                                                                     CNHierarchicComponentAccessPtr modelAccess,
                                                                     std::shared_ptr<QtSolutionItemFactory> itemFactory) {
    QtSolutionExplorerPtr view = QtSolutionExplorer::getNewInstance(itemFactory);
    CNSolutionExplorerPresenterPtr presenter = CNSolutionExplorerPresenter::getNewInstance(view, selectionModel);
    view->setListener(presenter);
    modelAccess->addListener(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makePropertiesExplorerComponent(CNSelectionModelPtr selectionModel,
                                                                       CNHierarchicComponentAccessPtr modelAccess,
                                                                       std::shared_ptr<QtPropertiesModelFactory> modelFactory) {
    QtPropertiesExplorerPtr view = QtPropertiesExplorer::getNewInstance(modelFactory);
    CNPropertiesExplorerPresenterPtr presenter = CNPropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
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
    CNMenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
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
    CNMenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    commandHistory->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}
CNComponentPtr QtViewComponentFactory::makeRemoveActionComponent(CNSelectionModelPtr selectionModel,
                                                                 std::shared_ptr<CNComponentInserter> model,
                                                                 CNCommandInvokerPtr invoker) {
    QtActionPtr view = makeQtAction();
    CNTransActionAppearancePtr appearance = makeCBTransActionAppearance(makeSelectionDependenAccessibility(selectionModel),
                                                                        makeCBFixedActionState(OFF),
                                                                        makeCBFixedActionTitle("Remove"));
    CNRemoveActionPtr action = CNRemoveAction::getNewInstance(selectionModel, model, invoker);
    CNMenuEntryPresenterPtr presenter = makeMenuEntryPresenter(view, appearance, action);
    selectionModel->attach(presenter);
    CNComposerPtr composer = makeCNNullComposer();

    return makeCNComposable(presenter, composer);
}

CNTransActionAppearancePtr QtViewComponentFactory::makeCBTransActionAppearance(CNTransActionAccessibilityPtr accessibility,
                                                                               CNTransActionStatePtr state,
                                                                               CNTransActionTitlePtr title) {
    return appearanceFactory->makeCNTransActionAppearance(accessibility, state, title);
}
CNTransActionAppearancePtr QtViewComponentFactory::makeCBFixedTransActionAppearance(bool accessibility, CNTransActionStateValues state, std::string title) {
    return appearanceFactory->makeCNFixedTransActionAppearance(accessibility, state, title);
}

CNTransActionStatePtr QtViewComponentFactory::makeCBFixedActionState(CNTransActionStateValues state) {
    return appearanceFactory->makeCNFixedActionState(state);
}
CNTransActionTitlePtr QtViewComponentFactory::makeCBFixedActionTitle(std::string title) {
    return appearanceFactory->makeCNFixedActionTitle(title);
}

CNTransActionAccessibilityPtr QtViewComponentFactory::makeUndoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNUndoDependentAccessibility::getNewInstance(commandHistory);
}
CNTransActionAccessibilityPtr QtViewComponentFactory::makeRedoDependenAccessibility(CNCommandHistoryPtr commandHistory) {
    return CNRedoDependentAccessibility::getNewInstance(commandHistory);
}
CNTransActionAccessibilityPtr QtViewComponentFactory::makeSelectionDependenAccessibility(CNSelectionModelPtr selectionModel) {
    return CNSelectionDependentAccessibility::getNewInstance(selectionModel);
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

CNMenuEntryPresenterPtr QtViewComponentFactory::makeMenuEntryPresenter(CNMenuEntryViewPtr view,
                                                                     CNTransActionAppearancePtr appearance,
                                                                     CNTransActionPtr action) {
    CNMenuEntryPresenterPtr presenter = CNMenuEntryPresenter::getNewInstance(view, appearance, action);
    view->setListener(presenter);
    return presenter;
}

CNDynamicMenuPresenterPtr QtViewComponentFactory::makeDynamicMenuPresenter(CNMenuViewPtr view,
                                                                std::shared_ptr<CNComposer> composer,
                                                                std::shared_ptr<CNComponentListProvider> listProvider) {
    return CNDynamicMenuPresenter::getNewInstance(view, composer, listProvider);
}
