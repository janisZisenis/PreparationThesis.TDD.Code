#include "QtViewComposableFactory.h"
#include <CrossNative/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNVisitingComposer.h>
#include <CrossNative/CNComposer/CNNullComposer.h>

#include "QtViews/QtShell/QtShell.h"
#include "QtViews/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QtShell/Visitors/QtShellDecomposingVisitor.h"

#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"

#include "QtViews/QtMenuBar/QtMenuBar.h"

QtViewComposableFactoryPtr QtViewComposableFactory::getNewInstance() {
    return QtViewComposableFactoryPtr();
}
QtViewComposableFactory::~QtViewComposableFactory() {}
QtViewComposableFactory::QtViewComposableFactory() {}

CNComposablePtr QtViewComposableFactory::makeShellComposable() {
    QtShellPtr shell = QtShell::getNewInstance();
    CNComposerPtr composer = makeVisitingComposer(QtShellComposingVisitor::getNewInstance(shell),
                                                  QtShellDecomposingVisitor::getNewInstance(shell));
    return makeComposable(shell, composer);
}

CNComposablePtr QtViewComposableFactory::makeSolutionExplorerComposable() {
    QtSolutionExplorerPtr solutionExplorer = QtSolutionExplorer::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(solutionExplorer, composer);
}

CNComposablePtr QtViewComposableFactory::makePropertiesExplorerComposable() {
    QtPropertiesExplorerPtr propertiesExplorer = QtPropertiesExplorer::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(propertiesExplorer, composer);
}

CNComposablePtr QtViewComposableFactory::makeMenuBarComposable() {
    QtMenuBarPtr menuBar = QtMenuBar::getNewInstance();
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(menuBar, composer);
}

CNComposablePtr QtViewComposableFactory::makeComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposable::getNewInstance(visitable, composer);
}

CNComposerPtr QtViewComposableFactory::makeVisitingComposer(CNVisitorPtr composing, CNVisitorPtr decomposing) {
    return CNVisitingComposer::getNewInstance(composing, decomposing);
}

CNComposerPtr QtViewComposableFactory::makeNullComposer() {
    return CNNullComposer::getNewInstance();
}
