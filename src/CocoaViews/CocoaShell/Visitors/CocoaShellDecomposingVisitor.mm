#include "CocoaShellDecomposingVisitor.h"
#include "CocoaViews/CocoaShell/CocoaShell.h"

#include "CocoaViews/CocoaSolutionExplorer/CocoaSolutionExplorer.h"
#include "CocoaViews/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"

CocoaShellDecomposingVisitorPtr CocoaShellDecomposingVisitor::getNewInstance(CocoaShellPtr shell) {
    return CocoaShellDecomposingVisitorPtr(new CocoaShellDecomposingVisitor(shell));
}
CocoaShellDecomposingVisitor::~CocoaShellDecomposingVisitor() {}
CocoaShellDecomposingVisitor::CocoaShellDecomposingVisitor(CocoaShellPtr shell) : shell(shell) {}

void CocoaShellDecomposingVisitor::visit(CocoaSolutionExplorerPtr solutionExplorer) {
    shell->removeNSView(solutionExplorer->getNSView(), LEFT);
}

void CocoaShellDecomposingVisitor::visit(CocoaPropertiesExplorerPtr propertiesExplorer) {
    shell->removeNSView(propertiesExplorer->getNSView(), RIGHT);
}


