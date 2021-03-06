#include "CocoaMenu.h"
#include "CocoaMenuVisitor.h"
#include <Hierarchies/CNTagged/CNTaggedVisitor.h>
#include <Hierarchies/CNAcceptor/CNAcceptorImp.h>
#import <Cocoa/Cocoa.h>

CocoaMenuPtr CocoaMenu::getNewInstance(std::string title) {
    return CocoaMenuPtr(new CocoaMenu(title));
}
CocoaMenu::~CocoaMenu() {}
CocoaMenu::CocoaMenu(std::string title)
        : typeAcceptor(CNAcceptorImp<CocoaMenuVisitor, CocoaMenu>::getNewInstance()),
          tagAcceptor(CNAcceptorImp<CNTaggedVisitor, CocoaMenu>::getNewInstance()),
          emptyMenuItem([[NSMenuItem alloc] initWithTitle:@"Empty" action:(SEL)nil keyEquivalent:@""]),
          menuItem([[NSMenuItem alloc] initWithTitle:[NSString stringWithUTF8String:title.c_str()] action:(SEL)nil keyEquivalent:@""]),
          menu([[NSMenu alloc] initWithTitle:[NSString stringWithUTF8String:title.c_str()]]) {
    initializeEmptyMenuItem();
    initializeMenu();
    initializeMenuItem();
}



NSMenuItem *CocoaMenu::getNSMenuItem() {
    return menuItem;
}

void CocoaMenu::addNSMenuItem(NSMenuItemBasedPtr nsMenuItemBased) {
    if(menuContainsEmptyMenuItem())
        removeEmptyMenuItemFromMenu();

    addToMenu(nsMenuItemBased->getNSMenuItem());
}
void CocoaMenu::removeNSMenuItem(NSMenuItemBasedPtr nsMenuItemBased) {
    removeFromMenu(nsMenuItemBased->getNSMenuItem());

    if(menuIsEmpty())
        addEmptyMenuItemToMenu();
}

void CocoaMenu::initializeMenuItem() {
    [menuItem setSubmenu: menu];
}
void CocoaMenu::initializeMenu() {
    disableAutoEnableMenuItems();
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
    return [menu.itemArray containsObject:emptyMenuItem];
}
void CocoaMenu::addEmptyMenuItemToMenu() {
    [menu addItem: emptyMenuItem];
}
void CocoaMenu::removeEmptyMenuItemFromMenu() {
    removeFromMenu(emptyMenuItem);
}

void CocoaMenu::accept(CNVisitorPtr visitor) {
    try {
        typeAcceptor->accept(visitor, me());
    } catch(CNVisitableVisitorMismatchException& e) {
        tagAcceptor->accept(visitor, me());
    }
}
std::string CocoaMenu::getTag() {
    return tag;
}
void CocoaMenu::setTag(std::string tag) {
    this->tag = tag;
}

CocoaMenuPtr CocoaMenu::me() {
    return this->shared_from_this();
}

void CocoaMenu::disableAutoEnableMenuItems() {
    [menu setAutoenablesItems: NO];
}


