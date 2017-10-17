#include "CocoaMenu.h"
#include "CocoaMenuVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#import <Cocoa/Cocoa.h>

CocoaMenuPtr CocoaMenu::getNewInstance(std::string title) {
    return CocoaMenuPtr(new CocoaMenu(title));
}
CocoaMenu::~CocoaMenu() {}
CocoaMenu::CocoaMenu(std::string title)
        : acceptor(CNAcceptorImp<CocoaMenuVisitor, CocoaMenu>::getNewInstance()),
          emptyMenuItem([[NSMenuItem alloc] initWithTitle:[NSString stringWithUTF8String:title.c_str()] action:(SEL)nil keyEquivalent:@""]),
          menuItem([[NSMenuItem alloc] initWithTitle:[NSString stringWithUTF8String:title.c_str()] action:(SEL)nil keyEquivalent:@""]),
          menu([[NSMenu alloc] initWithTitle:[NSString stringWithUTF8String:title.c_str()]]) {
    initializeEmptyMenuItem();
    initializeMenu();
    initializeMenuItem();
}



NSMenuItem *CocoaMenu::getNSMenuItem() {
    return menuItem;
}

void CocoaMenu::addNSMenuItem(NSMenuItem* nsMenuItem) {
    if(menuContainsEmptyMenuItem())
        removeEmptyMenuItemFromMenu();

    addToMenu(nsMenuItem);
}
void CocoaMenu::removeNSMenuItem(NSMenuItem* nsMenuItem) {
    removeFromMenu(nsMenuItem);

    if(menuIsEmpty())
        addEmptyMenuItemToMenu();
}

void CocoaMenu::initializeMenuItem() {
    [menuItem setSubmenu: menu];
}
void CocoaMenu::initializeMenu() {
    addEmptyMenuItemToMenu();
}
void CocoaMenu::initializeEmptyMenuItem() {
    [emptyMenuItem setEnabled:false];
}

void CocoaMenu::addToMenu(NSMenuItem *nsMenuItem) {
    [menu addItem: nsMenuItem];
}
void CocoaMenu::removeFromMenu(NSMenuItem *nsMenuItem) {
    [menu removeItem: nsMenuItem];
}

bool CocoaMenu::menuIsEmpty() {
    return [menu.itemArray count] == 0;
}
bool CocoaMenu::menuContainsEmptyMenuItem() {
    return false;
//    return menu->actions().contains(emptyAction);
}
void CocoaMenu::addEmptyMenuItemToMenu() {
    [menu addItem: emptyMenuItem];
}
void CocoaMenu::removeEmptyMenuItemFromMenu() {
    removeFromMenu(emptyMenuItem);
}

void CocoaMenu::accept(CNVisitorPtr visitor) {
//    acceptor->accept(visitor, me());
}

CocoaMenuPtr CocoaMenu::me() {
    return this->shared_from_this();
}