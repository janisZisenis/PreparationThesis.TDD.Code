#include "CocoaMenuItem.h"
#include "CocoaMenuItemVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#import <Cocoa/Cocoa.h>
#import "CocoaViews/CocoaActionListener/CocoaActionListener.h"

CocoaMenuItemPtr CocoaMenuItem::getNewInstance() {
    return CocoaMenuItemPtr(new CocoaMenuItem());
}
CocoaMenuItem::~CocoaMenuItem() {}
CocoaMenuItem::CocoaMenuItem()
        : acceptor(CNAcceptorImp<CocoaMenuItemVisitor, CocoaMenuItem>::getNewInstance()),
          menuItem([NSMenuItem new]),
          clickedAction([[CocoaActionListener alloc] initWithTarget:this]) {
    connectToMenuItem();
}

NSMenuItem *CocoaMenuItem::getNSMenuItem() {
    return menuItem;
}

void CocoaMenuItem::setTitle(std::string newTitle) {
    menuItem.title = [NSString stringWithUTF8String:newTitle.c_str()];
}

void CocoaMenuItem::setAccessibility(bool newAccessibility) {
    newAccessibility ? [menuItem setState:NSOnState] : [menuItem setState:NSOffState];
}

void CocoaMenuItem::setChecked(bool newAccessibility) {
    [menuItem setEnabled:newAccessibility];
}


void CocoaMenuItem::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

void CocoaMenuItem::connectToMenuItem() {
    [menuItem setAction:@selector(listen:)];
    [menuItem setTarget:clickedAction];
}


void CocoaMenuItem::onAction(NSObject *object, CocoaActionListener *action) {}

CocoaMenuItemPtr CocoaMenuItem::me() {
    return this->shared_from_this();
}

