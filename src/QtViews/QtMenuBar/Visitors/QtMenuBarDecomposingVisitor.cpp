#include "QtMenuBarDecomposingVisitor.h"
#include "QtViews/QtMenuBar/QtMenuBar.h"

QtMenuBarDecomposingVisitorPtr QtMenuBarDecomposingVisitor::getNewInstance(QtMenuBarPtr menuBar) {
    return QtMenuBarDecomposingVisitorPtr(new QtMenuBarDecomposingVisitor(menuBar));
}

QtMenuBarDecomposingVisitor::~QtMenuBarDecomposingVisitor() {}

QtMenuBarDecomposingVisitor::QtMenuBarDecomposingVisitor(QtMenuBarPtr menuBar) : menuBar(menuBar) {}