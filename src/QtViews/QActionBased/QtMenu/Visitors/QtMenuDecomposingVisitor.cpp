#include "QtMenuDecomposingVisitor.h"

#include "QtViews/QActionBased/QtMenu/QtMenu.h"
#include "QtViews/QActionBased/QtAction/QtAction.h"

QtMenuDecomposingVisitorPtr QtMenuDecomposingVisitor::getNewInstance(QtMenuPtr menu) {
    return QtMenuDecomposingVisitorPtr(new QtMenuDecomposingVisitor(menu));
}

QtMenuDecomposingVisitor::~QtMenuDecomposingVisitor() {}

QtMenuDecomposingVisitor::QtMenuDecomposingVisitor(QtMenuPtr menu) : menu(menu){}

void QtMenuDecomposingVisitor::visit(QtActionPtr action) {
    menu->removeQAction(action);
}

void QtMenuDecomposingVisitor::visit(QtMenuPtr menu) {
    this->menu->removeQAction(menu);
}

