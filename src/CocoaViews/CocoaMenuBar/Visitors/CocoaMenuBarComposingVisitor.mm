#include "CocoaMenuBarComposingVisitor.h"
#include "CocoaViews/CocoaMenuBar/CocoaMenuBar.h"

CocoaMenuBarComposingVisitorPtr CocoaMenuBarComposingVisitor::getNewInstance(CocoaMenuBarPtr menuBar) {
    return CocoaMenuBarComposingVisitorPtr(new CocoaMenuBarComposingVisitor(menuBar));
}

CocoaMenuBarComposingVisitor::~CocoaMenuBarComposingVisitor() {}

CocoaMenuBarComposingVisitor::CocoaMenuBarComposingVisitor(CocoaMenuBarPtr menuBar) : menuBar(menuBar) {}