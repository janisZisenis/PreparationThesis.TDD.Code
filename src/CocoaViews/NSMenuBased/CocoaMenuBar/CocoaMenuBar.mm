#include "CocoaMenuBar.h"
#include "CocoaMenuBarVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#import "Cocoa/Cocoa.h"

CocoaMenuBarPtr CocoaMenuBar::getNewInstance() {
    return CocoaMenuBarPtr(new CocoaMenuBar());
}
CocoaMenuBar::~CocoaMenuBar() {}
CocoaMenuBar::CocoaMenuBar()
        : acceptor(CNAcceptorImp<CocoaMenuBarVisitor, CocoaMenuBar>::getNewInstance()) {
    this->menuBar = [[NSMenu alloc] init];

    [[NSApplication sharedApplication] setMainMenu:menuBar];

    id appName = [[NSProcessInfo processInfo] processName];

    id appMenuItem = [NSMenuItem new];
    [menuBar addItem:appMenuItem];
        id appMenu = [NSMenu new];
        [appMenuItem setSubmenu:appMenu];

            NSMenu* servicesMenu = [NSMenu new];
            NSApp.servicesMenu = servicesMenu;

            id aboutItem = [[NSMenuItem alloc] initWithTitle:[@"About " stringByAppendingString:appName] action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
            [appMenu addItem:aboutItem];

            [appMenu addItem:[NSMenuItem separatorItem]];

            id preferencesItem = [[NSMenuItem alloc] initWithTitle:@"Preferences" action:NULL keyEquivalent:@","];
            [appMenu addItem:preferencesItem];

            [appMenu addItem:[NSMenuItem separatorItem]];

            id hideItem = [[NSMenuItem alloc] initWithTitle:[@"Hide " stringByAppendingString:appName] action:@selector(hide:) keyEquivalent:@"h"];
            [appMenu addItem:hideItem];

            id hideOthersItem = [[NSMenuItem alloc] initWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
            [hideOthersItem setKeyEquivalentModifierMask: NSEventModifierFlagOption | NSEventModifierFlagCommand];
            [appMenu addItem:hideOthersItem];

            id showAllItem = [[NSMenuItem alloc] initWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
            [appMenu addItem:showAllItem];

            [appMenu addItem:[NSMenuItem separatorItem]];

            id servicesItem = [[NSMenuItem alloc] initWithTitle:@"Services" action:NULL keyEquivalent:@""];
            [appMenu addItem:servicesItem];
                [servicesItem setSubmenu:servicesMenu];

            [appMenu addItem:[NSMenuItem separatorItem]];

            id quitMenuItem = [[NSMenuItem alloc] initWithTitle:[@"Quit " stringByAppendingString:appName] action:@selector(terminate:) keyEquivalent:@"q"];
            [appMenu addItem:quitMenuItem];
}

NSMenu* CocoaMenuBar::getNSMenu() {
    return this->menuBar;
}

void CocoaMenuBar::addNSMenuItem(NSMenuItem* nsMenuItem) {
    [menuBar addItem:nsMenuItem];
}

void CocoaMenuBar::removeNSMenuItem(NSMenuItem* nsMenuItem) {
    [menuBar removeItem:nsMenuItem];
}

void CocoaMenuBar::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

CocoaMenuBarPtr CocoaMenuBar::me() {
    return this->shared_from_this();
}

