#include "QtMenuBarDecomposingVisitor.h"
#include "QtViews/QtMenuBar/QtMenuBar.h"

#include "QtViews/QtMenu/QtMenu.h"

QtMenuBarDecomposingVisitorPtr QtMenuBarDecomposingVisitor::getNewInstance(QtMenuBarPtr menuBar) {
    return QtMenuBarDecomposingVisitorPtr(new QtMenuBarDecomposingVisitor(menuBar));
}

QtMenuBarDecomposingVisitor::~QtMenuBarDecomposingVisitor() {}

QtMenuBarDecomposingVisitor::QtMenuBarDecomposingVisitor(QtMenuBarPtr menuBar) : menuBar(menuBar) {}

void QtMenuBarDecomposingVisitor::visit(QtMenuPtr menu) {
    menuBar->addQAction(menu->getQAction());
}
