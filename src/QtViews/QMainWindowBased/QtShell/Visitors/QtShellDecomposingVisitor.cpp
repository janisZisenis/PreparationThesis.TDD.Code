#include "QtShellDecomposingVisitor.h"
#include "QtViews/QMainWindowBased/QtShell/QtShell.h"

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include "QtViews/QWidgetBased/QtCentral/QtCentral.h"

QtShellDecomposingVisitorPtr QtShellDecomposingVisitor::getNewInstance(QtShellPtr shell) {
    return QtShellDecomposingVisitorPtr(new QtShellDecomposingVisitor(shell));
}

QtShellDecomposingVisitor::~QtShellDecomposingVisitor() {}

QtShellDecomposingVisitor::QtShellDecomposingVisitor(QtShellPtr shell) : shell(shell) {}

void QtShellDecomposingVisitor::visit(QtMenuBarPtr menuBar) {
    shell->removeQMenuBar(menuBar);
}

void QtShellDecomposingVisitor::visit(QtSolutionExplorerPtr solutionExplorer) {
    shell->removeQtWidget(solutionExplorer, LEFT);
}

void QtShellDecomposingVisitor::visit(QtPropertiesExplorerPtr propertiesExplorer) {
    shell->removeQtWidget(propertiesExplorer, LEFT);
}

void QtShellDecomposingVisitor::visit(QtCentralPtr central) {
    shell->removeQtWidget(central, CENTRAL);
}