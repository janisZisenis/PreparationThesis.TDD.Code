#include "QtShellDecomposingVisitor.h"
#include "QtViews/QtShell/QtShell.h"

#include "QtViews/QtMenuBar/QtMenuBar.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"

QtShellDecomposingVisitorPtr QtShellDecomposingVisitor::getNewInstance(QtShellPtr shell) {
    return QtShellDecomposingVisitorPtr(new QtShellDecomposingVisitor(shell));
}

QtShellDecomposingVisitor::~QtShellDecomposingVisitor() {}

QtShellDecomposingVisitor::QtShellDecomposingVisitor(QtShellPtr shell) : shell(shell) {}

void QtShellDecomposingVisitor::visit(QtMenuBarPtr menuBar) {
    shell->removeQMenuBar(menuBar->getQMenuBar());
}

void QtShellDecomposingVisitor::visit(QtSolutionExplorerPtr solutionExplorer) {
    shell->removeQWidget(solutionExplorer->getQWidget(), LEFT);
}

void QtShellDecomposingVisitor::visit(std::shared_ptr<QtPropertiesExplorer> propertiesExplorer) {
    shell->removeQWidget(propertiesExplorer->getQWidget(), RIGHT);
}

