#include "CocoaViewComponentFactory.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

#include "CocoaViews/NSWindowBased/CocoaShell/CocoaShell.h"
#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellComposingVisitor.h"
#include "CocoaViews/NSWindowBased/CocoaShell/Visitors/CocoaShellDecomposingVisitor.h"

#include "CocoaViews/NSMenuBased/CocoaMenuBar/CocoaMenuBar.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/Visitors/CocoaMenuBarDecomposingVisitor.h"

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h"

#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerPresenter.h>
#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorer.h"

#include <CrossViews/PropertiesExplorerPresenter/PropertiesExplorerPresenter.h>
#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"

#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>
#include <CodeBaseImp/CBFixedActionAppearance/CBFixedAppearance.h>
#include <CodeBase/CBTransAction/CBNullTransAction.h>
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"

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

CNComponentPtr CocoaViewComponentFactory::makeMenuBarComponent() {
    CocoaMenuBarPtr menuBar = CocoaMenuBar::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(CocoaMenuBarComposingVisitor::getNewInstance(menuBar),
                                                  CocoaMenuBarDecomposingVisitor::getNewInstance(menuBar));

    return makeComposable(menuBar, composer);
}

CNComponentPtr CocoaViewComponentFactory::makeSolutionExplorerComponent(std::shared_ptr<SelectionModel> selectionModel) {
    CocoaSolutionExplorerPtr view = CocoaSolutionExplorer::getNewInstance();
    SolutionExplorerPresenterPtr presenter = SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}

CNComponentPtr CocoaViewComponentFactory::makePropertiesExplorerComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                          std::shared_ptr<HierarchicModelAccess> modelAccess) {
    CocoaPropertiesExplorerPtr view = CocoaPropertiesExplorer::getNewInstance();
    PropertiesExplorerPresenterPtr presenter = PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(presenter, composer);
}

CNComponentPtr CocoaViewComponentFactory::makeHelloWorldMenuComponent(std::string tag) {
    CocoaMenuPtr menu = CocoaMenu::getNewInstance("HelloWorld!");
    menu->setTag(tag);
    CNComposerPtr composer = makeVisitingComposer(CocoaMenuComposingVisitor::getNewInstance(menu),
                                                  CocoaMenuDecomposingVisitor::getNewInstance(menu));

    return makeComposable(menu, composer);
}

CNComponentPtr CocoaViewComponentFactory::makeExampleMenuItemComponent() {
    CocoaMenuItemPtr menuItem = CocoaMenuItem::getNewInstance();
    CBFixedAppearancePtr appearance = CBFixedAppearance::getNewInstance(false, OFF, "Example");
    CBNullTransActionPtr action = CBNullTransAction::getNewInstance();
    MenuEntryPresenterPtr presenter = MenuEntryPresenter::getNewInstance(menuItem, appearance, action);

    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(menuItem, composer);
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