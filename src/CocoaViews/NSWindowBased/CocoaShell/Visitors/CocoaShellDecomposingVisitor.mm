#include "CocoaShellDecomposingVisitor.h"
#include "CocoaViews/NSWindowBased/CocoaShell/CocoaShell.h"

#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorer.h"
#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"

CocoaShellDecomposingVisitorPtr CocoaShellDecomposingVisitor::getNewInstance(CocoaShellPtr shell) {
    return CocoaShellDecomposingVisitorPtr(new CocoaShellDecomposingVisitor(shell));
}
CocoaShellDecomposingVisitor::~CocoaShellDecomposingVisitor() {}
CocoaShellDecomposingVisitor::CocoaShellDecomposingVisitor(CocoaShellPtr shell) : shell(shell) {}

void CocoaShellDecomposingVisitor::visit(CocoaSolutionExplorerPtr solutionExplorer) {
    shell->removeNSView(solutionExplorer, LEFT);
}

void CocoaShellDecomposingVisitor::visit(CocoaPropertiesExplorerPtr propertiesExplorer) {
    shell->removeNSView(propertiesExplorer, RIGHT);
}


