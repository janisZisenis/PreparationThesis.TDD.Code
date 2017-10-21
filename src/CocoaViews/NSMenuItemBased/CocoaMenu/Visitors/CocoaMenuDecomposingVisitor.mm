#include "CocoaMenuDecomposingVisitor.h"

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"

CocoaMenuDecomposingVisitorPtr CocoaMenuDecomposingVisitor::getNewInstance(CocoaMenuPtr menu) {
    return CocoaMenuDecomposingVisitorPtr(new CocoaMenuDecomposingVisitor(menu));
}

CocoaMenuDecomposingVisitor::~CocoaMenuDecomposingVisitor() {}

CocoaMenuDecomposingVisitor::CocoaMenuDecomposingVisitor(CocoaMenuPtr menu) : menu(menu){}

void CocoaMenuDecomposingVisitor::visit(CocoaMenuItemPtr menuItem) {
    menu->removeNSMenuItem(menuItem);
}

void CocoaMenuDecomposingVisitor::visit(CocoaMenuPtr menu) {
    this->menu->removeNSMenuItem(menu);
}

