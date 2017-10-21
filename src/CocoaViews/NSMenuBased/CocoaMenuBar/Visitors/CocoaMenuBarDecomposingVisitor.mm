#include "CocoaMenuBarDecomposingVisitor.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/CocoaMenuBar.h"

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"

CocoaMenuBarDecomposingVisitorPtr CocoaMenuBarDecomposingVisitor::getNewInstance(CocoaMenuBarPtr menuBar) {
    return CocoaMenuBarDecomposingVisitorPtr(new CocoaMenuBarDecomposingVisitor(menuBar));
}

CocoaMenuBarDecomposingVisitor::~CocoaMenuBarDecomposingVisitor() {}

CocoaMenuBarDecomposingVisitor::CocoaMenuBarDecomposingVisitor(CocoaMenuBarPtr menuBar) : menuBar(menuBar) {}

void CocoaMenuBarDecomposingVisitor::visit(CocoaMenuPtr menu) {
    menuBar->removeNSMenuItem(menu->getNSMenuItem());
}
