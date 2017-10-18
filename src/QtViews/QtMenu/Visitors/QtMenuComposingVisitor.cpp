#include "QtMenuComposingVisitor.h"

#include "QtViews/QtMenu/QtMenu.h"
#include "QtViews/QtAction/QtAction.h"

QtMenuComposingVisitorPtr QtMenuComposingVisitor::getNewInstance(QtMenuPtr menu) {
    return QtMenuComposingVisitorPtr(new QtMenuComposingVisitor(menu));
}

QtMenuComposingVisitor::~QtMenuComposingVisitor() {}

QtMenuComposingVisitor::QtMenuComposingVisitor(QtMenuPtr menu) : menu(menu){}

void QtMenuComposingVisitor::visit(QtActionPtr action) {
    menu->addQAction(action->getQAction());
}

void QtMenuComposingVisitor::visit(QtMenuPtr menu) {
    this->menu->addQAction(menu->getQAction());
}

