#include "QtMenuBarComposingVisitor.h"
#include "QtViews/QtMenuBar/QtMenuBar.h"

QtMenuBarComposingVisitorPtr QtMenuBarComposingVisitor::getNewInstance(QtMenuBarPtr menuBar) {
    return QtMenuBarComposingVisitorPtr(new QtMenuBarComposingVisitor(menuBar));
}

QtMenuBarComposingVisitor::~QtMenuBarComposingVisitor() {}

QtMenuBarComposingVisitor::QtMenuBarComposingVisitor(QtMenuBarPtr menuBar) : menuBar(menuBar) {}