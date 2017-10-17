#include "QtViewComponentFactory.h"
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

#include "QtViews/QtShell/QtShell.h"
#include "QtViews/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QtShell/Visitors/QtShellDecomposingVisitor.h"

#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"

#include "QtViews/QtMenuBar/QtMenuBar.h"

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

CNComponentPtr QtViewComponentFactory::makeSolutionExplorerComponent() {
    QtSolutionExplorerPtr solutionExplorer = QtSolutionExplorer::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(solutionExplorer, composer);
}

CNComponentPtr QtViewComponentFactory::makePropertiesExplorerComponent() {
    QtPropertiesExplorerPtr propertiesExplorer = QtPropertiesExplorer::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(propertiesExplorer, composer);
}

CNComponentPtr QtViewComponentFactory::makeMenuBarComponent() {
    QtMenuBarPtr menuBar = QtMenuBar::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(menuBar, composer);
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
