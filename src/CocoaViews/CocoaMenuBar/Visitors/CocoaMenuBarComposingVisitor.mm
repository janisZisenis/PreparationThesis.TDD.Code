#include "CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/CocoaMenuBar/CocoaMenuBar.h"

#include "CocoaViews/CocoaMenu/CocoaMenu.h"

CocoaMenuBarComposingVisitorPtr CocoaMenuBarComposingVisitor::getNewInstance(CocoaMenuBarPtr menuBar) {
    return CocoaMenuBarComposingVisitorPtr(new CocoaMenuBarComposingVisitor(menuBar));
}

CocoaMenuBarComposingVisitor::~CocoaMenuBarComposingVisitor() {}

CocoaMenuBarComposingVisitor::CocoaMenuBarComposingVisitor(CocoaMenuBarPtr menuBar) : menuBar(menuBar) {}

void CocoaMenuBarComposingVisitor::visit(CocoaMenuPtr menu) {
    menuBar->addNSMenuItem(menu->getNSMenuItem());
}
