#include "QtShellDecomposingVisitor.h"
#include "QtViews/QtShell/QtShell.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"

QtShellDecomposingVisitorPtr QtShellDecomposingVisitor::getNewInstance(QtShellPtr shell) {
    return QtShellDecomposingVisitorPtr(new QtShellDecomposingVisitor(shell));
}

QtShellDecomposingVisitor::~QtShellDecomposingVisitor() {}

QtShellDecomposingVisitor::QtShellDecomposingVisitor(QtShellPtr shell) : shell(shell) {}

void QtShellDecomposingVisitor::visit(QtSolutionExplorerPtr solutionExplorer) {
    shell->removeQWidget(solutionExplorer->getQWidget(), LEFT);
}
