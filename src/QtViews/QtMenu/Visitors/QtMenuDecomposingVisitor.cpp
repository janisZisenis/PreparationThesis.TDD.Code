#include "QtMenuDecomposingVisitor.h"

#include "QtViews/QtMenu/QtMenu.h"
#include "QtViews/QtAction/QtAction.h"

QtMenuDecomposingVisitorPtr QtMenuDecomposingVisitor::getNewInstance(QtMenuPtr menu) {
    return QtMenuDecomposingVisitorPtr(new QtMenuDecomposingVisitor(menu));
}

QtMenuDecomposingVisitor::~QtMenuDecomposingVisitor() {}

QtMenuDecomposingVisitor::QtMenuDecomposingVisitor(QtMenuPtr menu) : menu(menu){}

void QtMenuDecomposingVisitor::visit(QtActionPtr action) {
    menu->removeQAction(action->getQAction());
}

void QtMenuDecomposingVisitor::visit(QtMenuPtr menu) {
    this->menu->removeQAction(menu->getQAction());
}

