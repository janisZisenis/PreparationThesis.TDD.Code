#include "QtMenuBarComposingVisitor.h"
#include "QtViews/QMenuBarBased/QtMenuBar/QtMenuBar.h"

#include "QtViews/QActionBased/QtMenu/QtMenu.h"

QtMenuBarComposingVisitorPtr QtMenuBarComposingVisitor::getNewInstance(QtMenuBarPtr menuBar) {
    return QtMenuBarComposingVisitorPtr(new QtMenuBarComposingVisitor(menuBar));
}

QtMenuBarComposingVisitor::~QtMenuBarComposingVisitor() {}

QtMenuBarComposingVisitor::QtMenuBarComposingVisitor(QtMenuBarPtr menuBar) : menuBar(menuBar) {}

void QtMenuBarComposingVisitor::visit(QtMenuPtr menu) {
    menuBar->addQAction(menu);
}
