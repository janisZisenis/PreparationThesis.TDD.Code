#include "CocoaViewComponentFactory.h"
#include <CrossNative/CNComponent/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

#include "CocoaViews/CocoaShell/CocoaShell.h"
#include "CocoaViews/CocoaShell/Visitors/CocoaShellComposingVisitor.h"
#include "CocoaViews/CocoaShell/Visitors/CocoaShellDecomposingVisitor.h"

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

CNComponentPtr CocoaViewComponentFactory::makeComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposable::getNewInstance(visitable, composer);
}

CNComposerPtr CocoaViewComponentFactory::makeVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return CNVisitingComposer::getNewInstance(composing, decomposing);
}

CNComposerPtr CocoaViewComponentFactory::makeNullComposer() {
    return CNNullComposer::getNewInstance();
}

