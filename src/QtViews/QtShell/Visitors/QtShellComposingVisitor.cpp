#include "QtShellComposingVisitor.h"
#include "QtViews/QtShell/QtShell.h"

#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"

QtShellComposingVisitorPtr QtShellComposingVisitor::getNewInstance(std::shared_ptr<QtShell> shell) {
    return QtShellComposingVisitorPtr(new QtShellComposingVisitor(shell));
}

QtShellComposingVisitor::~QtShellComposingVisitor() {}

QtShellComposingVisitor::QtShellComposingVisitor(QtShellPtr shell) : shell(shell) {}

void QtShellComposingVisitor::visit(QtSolutionExplorerPtr solutionExplorer) {
    shell->addQWidget(solutionExplorer->getQWidget(), LEFT);
}
