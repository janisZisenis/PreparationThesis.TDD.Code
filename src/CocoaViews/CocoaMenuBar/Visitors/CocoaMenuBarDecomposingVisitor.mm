#include "CocoaMenuBarDecomposingVisitor.h"
#include "CocoaViews/CocoaMenuBar/CocoaMenuBar.h"

#include "CocoaViews/CocoaMenu/CocoaMenu.h"

CocoaMenuBarDecomposingVisitorPtr CocoaMenuBarDecomposingVisitor::getNewInstance(CocoaMenuBarPtr menuBar) {
    return CocoaMenuBarDecomposingVisitorPtr(new CocoaMenuBarDecomposingVisitor(menuBar));
}

CocoaMenuBarDecomposingVisitor::~CocoaMenuBarDecomposingVisitor() {}

CocoaMenuBarDecomposingVisitor::CocoaMenuBarDecomposingVisitor(CocoaMenuBarPtr menuBar) : menuBar(menuBar) {}

void CocoaMenuBarDecomposingVisitor::visit(CocoaMenuPtr menu) {
    menu->removeNSMenuItem(menu->getNSMenuItem());
}
