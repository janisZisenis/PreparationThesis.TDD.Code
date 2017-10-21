#include "QtViewComponentFactory.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

#include "QtViews/QMainWindowBased/QtShell/QtShell.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QMainWindowBased/QtShell/Visitors/QtShellDecomposingVisitor.h"

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarComposingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/Visitors/QtMenuBarDecomposingVisitor.h"

#include "QtViews/QActionBased/QtMenu/QtMenu.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuComposingVisitor.h"
#include "QtViews/QActionBased/QtMenu/Visitors/QtMenuDecomposingVisitor.h"

#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerPresenter.h>
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorer.h"

#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include <CrossViews/PropertiesExplorerPresenter/PropertiesExplorerPresenter.h>

#include <CodeBaseImp/CBFixedActionAppearance/CBFixedAppearance.h>
#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>
#include "QtViews/QActionBased/QtAction/QtAction.h"
#include <CodeBase/CBTransAction/CBNullTransAction.h>

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

CNComponentPtr QtViewComponentFactory::makeSolutionExplorerComponent(std::shared_ptr<SelectionModel> selectionModel) {
    QtSolutionExplorerPtr view = QtSolutionExplorer::getNewInstance();
    SolutionExplorerPresenterPtr presenter = SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}

CNComponentPtr QtViewComponentFactory::makeMenuBarComponent() {
    QtMenuBarPtr menuBar = QtMenuBar::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(QtMenuBarComposingVisitor::getNewInstance(menuBar),
                                                  QtMenuBarDecomposingVisitor::getNewInstance(menuBar));

    return makeComposable(menuBar, composer);
}

CNComponentPtr QtViewComponentFactory::makePropertiesExplorerComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                       std::shared_ptr<HierarchicModelAccess> modelAccess) {
    QtPropertiesExplorerPtr view = QtPropertiesExplorer::getNewInstance();
    PropertiesExplorerPresenterPtr presenter = PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
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
    QtActionPtr view = QtAction::getNewInstance();
    CBFixedAppearancePtr appearance = CBFixedAppearance::getNewInstance(false, OFF, "Example");
    CBNullTransActionPtr action = CBNullTransAction::getNewInstance();
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(view, appearance, action);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
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
