#include "QtShellComposingVisitor.h"
#include "QtViews/QMainWindowBased/QtShell/QtShell.h"

#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"
#include "QtViews/QWidgetBased/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QWidgetBased/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include "QtViews/QWidgetBased/QtCentral/QtCentral.h"

QtShellComposingVisitorPtr QtShellComposingVisitor::getNewInstance(QtShellPtr shell) {
    return QtShellComposingVisitorPtr(new QtShellComposingVisitor(shell));
}

QtShellComposingVisitor::~QtShellComposingVisitor() {}

QtShellComposingVisitor::QtShellComposingVisitor(QtShellPtr shell) : shell(shell) {}

void QtShellComposingVisitor::visit(QtMenuBarPtr menuBar) {
    shell->addQMenuBar(menuBar);
}

void QtShellComposingVisitor::visit(QtSolutionExplorerPtr solutionExplorer) {
    shell->addQtWidget(solutionExplorer, LEFT);
}

void QtShellComposingVisitor::visit(QtPropertiesExplorerPtr propertiesExplorer) {
    shell->addQtWidget(propertiesExplorer, LEFT);
}

void QtShellComposingVisitor::visit(QtCentralPtr central) {
    shell->addQtWidget(central, CENTRAL);
}
