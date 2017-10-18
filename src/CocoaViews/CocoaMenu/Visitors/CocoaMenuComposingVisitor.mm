#include "CocoaMenuComposingVisitor.h"

#include "CocoaViews/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/CocoaMenuItem/CocoaMenuItem.h"

CocoaMenuComposingVisitorPtr CocoaMenuComposingVisitor::getNewInstance(CocoaMenuPtr menu) {
    return CocoaMenuComposingVisitorPtr(new CocoaMenuComposingVisitor(menu));
}

CocoaMenuComposingVisitor::~CocoaMenuComposingVisitor() {}

CocoaMenuComposingVisitor::CocoaMenuComposingVisitor(CocoaMenuPtr menu) : menu(menu){}

void CocoaMenuComposingVisitor::visit(CocoaMenuItemPtr menuItem) {
    menu->addNSMenuItem(menuItem->getNSMenuItem());
}

void CocoaMenuComposingVisitor::visit(CocoaMenuPtr menu) {
    this->menu->addNSMenuItem(menu->getNSMenuItem());
}

