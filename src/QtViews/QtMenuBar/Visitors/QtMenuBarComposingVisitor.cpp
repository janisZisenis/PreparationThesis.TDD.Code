#include "QtMenuBarComposingVisitor.h"
#include "QtViews/QtMenuBar/QtMenuBar.h"

#include "QtViews/QtMenu/QtMenu.h"

QtMenuBarComposingVisitorPtr QtMenuBarComposingVisitor::getNewInstance(QtMenuBarPtr menuBar) {
    return QtMenuBarComposingVisitorPtr(new QtMenuBarComposingVisitor(menuBar));
}

QtMenuBarComposingVisitor::~QtMenuBarComposingVisitor() {}

QtMenuBarComposingVisitor::QtMenuBarComposingVisitor(QtMenuBarPtr menuBar) : menuBar(menuBar) {}

void QtMenuBarComposingVisitor::visit(QtMenuPtr menu) {
    menuBar->addQAction(menu->getQAction());
}
