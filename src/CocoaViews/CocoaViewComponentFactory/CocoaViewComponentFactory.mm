#include "CocoaViewComponentFactory.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

#include "CocoaViews/CocoaShell/CocoaShell.h"
#include "CocoaViews/CocoaShell/Visitors/CocoaShellComposingVisitor.h"
#include "CocoaViews/CocoaShell/Visitors/CocoaShellDecomposingVisitor.h"

#include "CocoaViews/CocoaMenuBar/CocoaMenuBar.h"
#include "CocoaViews/CocoaMenuBar/Visitors/CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/CocoaMenuBar/Visitors/CocoaMenuBarDecomposingVisitor.h"

#include "CocoaViews/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/CocoaMenu/Visitors/CocoaMenuComposingVisitor.h"
#include "CocoaViews/CocoaMenu/Visitors/CocoaMenuDecomposingVisitor.h"

#include "CocoaViews/CocoaSolutionExplorer/CocoaSolutionExplorer.h"
#include "CocoaViews/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"

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

CNComponentPtr CocoaViewComponentFactory::makeSolutionExplorerComponent() {
    CocoaSolutionExplorerPtr solutionExplorer = CocoaSolutionExplorer::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(solutionExplorer, composer);
}

CNComponentPtr CocoaViewComponentFactory::makePropertiesExplorerComponent() {
    CocoaPropertiesExplorerPtr propertiesExplorer = CocoaPropertiesExplorer::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(propertiesExplorer, composer);
}

CNComponentPtr CocoaViewComponentFactory::makeHelloWorldMenuComponent(std::string tag) {
    CocoaMenuPtr menu = CocoaMenu::getNewInstance("HelloWorld!");
    menu->setTag(tag);
    CNComposerPtr composer = makeVisitingComposer(CocoaMenuComposingVisitor::getNewInstance(menu),
                                                  CocoaMenuDecomposingVisitor::getNewInstance(menu));

    return makeComposable(menu, composer);
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

