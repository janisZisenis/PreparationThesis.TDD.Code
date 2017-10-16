#include "CocoaShellComposingVisitor.h"
#include "CocoaViews/CocoaShell/CocoaShell.h"

#include "CocoaViews/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"
#include "CocoaViews/CocoaSolutionExplorer/CocoaSolutionExplorer.h"

CocoaShellComposingVisitorPtr CocoaShellComposingVisitor::getNewInstance(CocoaShellPtr shell) {
    return CocoaShellComposingVisitorPtr(new CocoaShellComposingVisitor(shell));
}

CocoaShellComposingVisitor::~CocoaShellComposingVisitor() {}

CocoaShellComposingVisitor::CocoaShellComposingVisitor(CocoaShellPtr shell) : shell(shell) {}

void CocoaShellComposingVisitor::visit(CocoaSolutionExplorerPtr solutionExplorer) {
    shell->addNSView(solutionExplorer->getNSView(), LEFT);
}

void CocoaShellComposingVisitor::visit(CocoaPropertiesExplorerPtr propertiesExplorer) {
    shell->addNSView(propertiesExplorer->getNSView(), LEFT);
}

