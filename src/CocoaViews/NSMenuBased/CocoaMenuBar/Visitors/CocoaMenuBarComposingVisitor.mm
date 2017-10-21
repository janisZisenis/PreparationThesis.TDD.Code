#include "CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/NSMenuBased/CocoaMenuBar/CocoaMenuBar.h"

#include "CocoaViews/NSMenuItemBased/CocoaMenu/CocoaMenu.h"

CocoaMenuBarComposingVisitorPtr CocoaMenuBarComposingVisitor::getNewInstance(CocoaMenuBarPtr menuBar) {
    return CocoaMenuBarComposingVisitorPtr(new CocoaMenuBarComposingVisitor(menuBar));
}

CocoaMenuBarComposingVisitor::~CocoaMenuBarComposingVisitor() {}

CocoaMenuBarComposingVisitor::CocoaMenuBarComposingVisitor(CocoaMenuBarPtr menuBar) : menuBar(menuBar) {}

void CocoaMenuBarComposingVisitor::visit(CocoaMenuPtr menu) {
    menuBar->addNSMenuItem(menu->getNSMenuItem());
}
