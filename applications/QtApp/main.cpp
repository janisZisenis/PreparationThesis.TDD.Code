#include <QApplication>

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>
#include <CrossNative/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include <CrossNative/CNComposer/CNVisitingComposer.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>
#include <CrossNative/CNMatcher/CNTypeMatcher.h>

#include "QtViews/QtViewComposableFactory/QtViewComposableFactory.h"

#include "QtViews/QtShell/QtShell.h"
#include "QtViews/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QtShell/Visitors/QtShellDecomposingVisitor.h"
#include "QtViews/QtShell/Visitors/QtShellNullVisitor.h"

#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtMenuBar/QtMenuBar.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtViewComposableFactoryPtr factory = QtViewComposableFactory::getNewInstance();

    QtShellPtr shell = QtShell::getNewInstance();
    CNVisitingComposerPtr shellComposer = CNVisitingComposer::getNewInstance(QtShellComposingVisitor::getNewInstance(shell), QtShellDecomposingVisitor::getNewInstance(shell));

    CNComposablePtr shellComposable = factory->makeShellComposable();
    CNComposablePtr solutionExplorerComposable = factory->makeSolutionExplorerComposable();
    CNComposablePtr propertiesExplorerComposable = factory->makePropertiesExplorerComposable();
    CNComposablePtr menuBarComposable = factory->makeMenuBarComposable();

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(shellComposable, CNNullMatcher::getNewInstance());
    viewHierarchy->load(solutionExplorerComposable, CNTypeMatcher::getNewInstance(QtShellNullVisitor::getNewInstance()));
    viewHierarchy->load(propertiesExplorerComposable, CNTypeMatcher::getNewInstance(QtShellNullVisitor::getNewInstance()));
    viewHierarchy->load(menuBarComposable, CNTypeMatcher::getNewInstance(QtShellNullVisitor::getNewInstance()));

    return a.exec();
}