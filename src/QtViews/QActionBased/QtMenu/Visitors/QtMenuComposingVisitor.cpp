#include "QtMenuComposingVisitor.h"

#include "QtViews/QActionBased/QtMenu/QtMenu.h"
#include "QtViews/QActionBased/QtAction/QtAction.h"

QtMenuComposingVisitorPtr QtMenuComposingVisitor::getNewInstance(QtMenuPtr menu) {
    return QtMenuComposingVisitorPtr(new QtMenuComposingVisitor(menu));
}

QtMenuComposingVisitor::~QtMenuComposingVisitor() {}

QtMenuComposingVisitor::QtMenuComposingVisitor(QtMenuPtr menu) : menu(menu){}

void QtMenuComposingVisitor::visit(QtActionPtr action) {
    menu->addQAction(action);
}

void QtMenuComposingVisitor::visit(QtMenuPtr menu) {
    this->menu->addQAction(menu);
}

