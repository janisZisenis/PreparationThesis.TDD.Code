#include "CocoaShellComposingVisitor.h"
#include "CocoaViews/CocoaShell/CocoaShell.h"

#include "CocoaViews/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"

CocoaShellComposingVisitorPtr CocoaShellComposingVisitor::getNewInstance(CocoaShellPtr shell) {
    return CocoaShellComposingVisitorPtr(new CocoaShellComposingVisitor(shell));
}

CocoaShellComposingVisitor::~CocoaShellComposingVisitor() {}

CocoaShellComposingVisitor::CocoaShellComposingVisitor(CocoaShellPtr shell) : shell(shell) {}

void CocoaShellComposingVisitor::visit(CocoaPropertiesExplorerPtr propertiesExplorer) {
    shell->addNSView(propertiesExplorer->getNSView(), LEFT);
}
