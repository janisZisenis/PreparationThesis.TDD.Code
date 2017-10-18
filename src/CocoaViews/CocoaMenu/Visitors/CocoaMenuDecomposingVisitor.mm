#include "CocoaMenuDecomposingVisitor.h"

#include "CocoaViews/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/CocoaMenuItem/CocoaMenuItem.h"

CocoaMenuDecomposingVisitorPtr CocoaMenuDecomposingVisitor::getNewInstance(CocoaMenuPtr menu) {
    return CocoaMenuDecomposingVisitorPtr(new CocoaMenuDecomposingVisitor(menu));
}

CocoaMenuDecomposingVisitor::~CocoaMenuDecomposingVisitor() {}

CocoaMenuDecomposingVisitor::CocoaMenuDecomposingVisitor(CocoaMenuPtr menu) : menu(menu){}

void CocoaMenuDecomposingVisitor::visit(CocoaMenuItemPtr menuItem) {
    menu->removeNSMenuItem(menuItem->getNSMenuItem());
}

void CocoaMenuDecomposingVisitor::visit(CocoaMenuPtr menu) {
    this->menu->removeNSMenuItem(menu->getNSMenuItem());
}

