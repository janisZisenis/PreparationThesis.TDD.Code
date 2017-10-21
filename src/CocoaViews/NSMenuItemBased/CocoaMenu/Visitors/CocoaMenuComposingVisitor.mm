#include "CocoaMenuComposingVisitor.h"

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"
#include "CocoaViews/NSMenuItemBased/CocoaMenuItem/CocoaMenuItem.h"

CocoaMenuComposingVisitorPtr CocoaMenuComposingVisitor::getNewInstance(CocoaMenuPtr menu) {
    return CocoaMenuComposingVisitorPtr(new CocoaMenuComposingVisitor(menu));
}

CocoaMenuComposingVisitor::~CocoaMenuComposingVisitor() {}

CocoaMenuComposingVisitor::CocoaMenuComposingVisitor(CocoaMenuPtr menu) : menu(menu){}

void CocoaMenuComposingVisitor::visit(CocoaMenuItemPtr menuItem) {
    menu->addNSMenuItem(menuItem);
}

void CocoaMenuComposingVisitor::visit(CocoaMenuPtr menu) {
    this->menu->addNSMenuItem(menu);
}

