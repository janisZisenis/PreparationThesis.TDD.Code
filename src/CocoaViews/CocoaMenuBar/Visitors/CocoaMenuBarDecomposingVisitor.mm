#include "CocoaMenuBarDecomposingVisitor.h"
#include "CocoaViews/CocoaMenuBar/CocoaMenuBar.h"

CocoaMenuBarDecomposingVisitorPtr CocoaMenuBarDecomposingVisitor::getNewInstance(CocoaMenuBarPtr menuBar) {
    return CocoaMenuBarDecomposingVisitorPtr(new CocoaMenuBarDecomposingVisitor(menuBar));
}

CocoaMenuBarDecomposingVisitor::~CocoaMenuBarDecomposingVisitor() {}

CocoaMenuBarDecomposingVisitor::CocoaMenuBarDecomposingVisitor(CocoaMenuBarPtr menuBar) : menuBar(menuBar) {}