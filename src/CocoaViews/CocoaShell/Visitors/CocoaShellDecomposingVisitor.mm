#include "CocoaShellDecomposingVisitor.h"
#include "CocoaViews/CocoaShell/CocoaShell.h"

#include "CocoaViews/CocoaPropertiesExplorer/CocoaPropertiesExplorer.h"

CocoaShellDecomposingVisitorPtr CocoaShellDecomposingVisitor::getNewInstance(CocoaShellPtr shell) {
    return CocoaShellDecomposingVisitorPtr(new CocoaShellDecomposingVisitor(shell));
}
CocoaShellDecomposingVisitor::~CocoaShellDecomposingVisitor() {}
CocoaShellDecomposingVisitor::CocoaShellDecomposingVisitor(CocoaShellPtr shell) : shell(shell) {}

void CocoaShellDecomposingVisitor::visit(std::shared_ptr<CocoaPropertiesExplorer> propertiesExplorer) {
    shell->removeNSView(propertiesExplorer->getNSView(), RIGHT);
}

