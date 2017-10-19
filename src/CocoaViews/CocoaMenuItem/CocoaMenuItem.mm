#include "CocoaMenuItem.h"
#include "CocoaMenuItemVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
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

void CocoaMenuItem::check() {
    setState(NSOnState);
}

void CocoaMenuItem::uncheck() {
    setState(NSOffState);
}

void CocoaMenuItem::enable() {
    setEnabled(true);
}

void CocoaMenuItem::disable() {
    setEnabled(false);
}

void CocoaMenuItem::setState(const NSControlStateValue state) {
    [menuItem setState:state];
}

void CocoaMenuItem::setEnabled(bool enabled) {
    [menuItem setEnabled:enabled];
}

void CocoaMenuItem::connectToMenuItem() {
    [menuItem setAction:@selector(listen:)];
    [menuItem setTarget:clickedAction];
}

void CocoaMenuItem::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

CocoaMenuItemPtr CocoaMenuItem::me() {
    return this->shared_from_this();
}

void CocoaMenuItem::onAction(NSObject *object, CocoaActionListener *action) {}
