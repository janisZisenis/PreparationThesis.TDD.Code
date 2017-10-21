#include "CocoaShellComposingVisitor.h"
#include "CocoaViews/NSWindowBased/CocoaShell/CocoaShell.h"

#include "CocoaViews/NSViewBased/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"
#include "CocoaViews/NSViewBased/CocoaSolutionExplorer/CocoaSolutionExplorer.h"

CocoaShellComposingVisitorPtr CocoaShellComposingVisitor::getNewInstance(CocoaShellPtr shell) {
    return CocoaShellComposingVisitorPtr(new CocoaShellComposingVisitor(shell));
}

CocoaShellComposingVisitor::~CocoaShellComposingVisitor() {}

CocoaShellComposingVisitor::CocoaShellComposingVisitor(CocoaShellPtr shell) : shell(shell) {}

void CocoaShellComposingVisitor::visit(CocoaSolutionExplorerPtr solutionExplorer) {
    shell->addNSView(solutionExplorer, RIGHT);
}

void CocoaShellComposingVisitor::visit(CocoaPropertiesExplorerPtr propertiesExplorer) {
    shell->addNSView(propertiesExplorer, LEFT);
}

