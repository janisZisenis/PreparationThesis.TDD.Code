#include "QtShellComposingVisitor.h"
#include "QtViews/QtShell/QtShell.h"

#include "QtViews/QtMenuBar/QtMenuBar.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"

QtShellComposingVisitorPtr QtShellComposingVisitor::getNewInstance(QtShellPtr shell) {
    return QtShellComposingVisitorPtr(new QtShellComposingVisitor(shell));
}

QtShellComposingVisitor::~QtShellComposingVisitor() {}

QtShellComposingVisitor::QtShellComposingVisitor(QtShellPtr shell) : shell(shell) {}

void QtShellComposingVisitor::visit(QtMenuBarPtr menuBar) {
    shell->addQMenuBar(menuBar->getQMenuBar());
}

void QtShellComposingVisitor::visit(QtSolutionExplorerPtr solutionExplorer) {
    shell->addQWidget(solutionExplorer->getQWidget(), LEFT);
}

void QtShellComposingVisitor::visit(QtPropertiesExplorerPtr propertiesExplorer) {
    shell->addQWidget(propertiesExplorer->getQWidget(), RIGHT);
}