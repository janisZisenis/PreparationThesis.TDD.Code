#include "QtShellDecomposingVisitor.h"
#include "QtViews/QtShell/QtShell.h"

QtShellDecomposingVisitorPtr QtShellDecomposingVisitor::getNewInstance(QtShellPtr shell) {
    return QtShellDecomposingVisitorPtr(new QtShellDecomposingVisitor(shell));
}

QtShellDecomposingVisitor::~QtShellDecomposingVisitor() {}

QtShellDecomposingVisitor::QtShellDecomposingVisitor(QtShellPtr shell) : shell(shell) {}
