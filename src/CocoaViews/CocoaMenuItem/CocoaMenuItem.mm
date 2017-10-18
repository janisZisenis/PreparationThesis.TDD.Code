#include "CocoaMenuItem.h"
#import <Cocoa/Cocoa.h>
#import "CocoaViews/CocoaActionListener/CocoaActionListener.h"

CocoaMenuItemPtr CocoaMenuItem::getNewInstance() {
    return CocoaMenuItemPtr(new CocoaMenuItem());
}
CocoaMenuItem::~CocoaMenuItem() {}
CocoaMenuItem::CocoaMenuItem()
        : menuItem([NSMenuItem new]),
          clickedAction([[CocoaActionListener alloc] initWithTarget:this]) {
    connectToMenuItem();
}

NSMenuItem *CocoaMenuItem::getNSMenuItem() {
    return menuItem;
}

void CocoaMenuItem::connectToMenuItem() {
    [menuItem setAction:@selector(listen:)];
    [menuItem setTarget:clickedAction];
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

void CocoaMenuItem::onAction(NSObject *object, CocoaActionListener *action) {}
