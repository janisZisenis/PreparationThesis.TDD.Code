#include "CocoaShell.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include "CocoaShellVisitor.h"
#import <AppKit/AppKit.h>
#include "CocoaViews/NSViewBased/NSViewBased.h"

CocoaShellPtr CocoaShell::getNewInstance() {
    return CocoaShellPtr(new CocoaShell());
}

CocoaShell::~CocoaShell() {}

CocoaShell::CocoaShell() : acceptor(CNAcceptorImp<CocoaShellVisitor, CocoaShell>::getNewInstance()){
    initWindow();
    initComponents();
    composeWindow();
    updateSideBarWidths();
}

void CocoaShell::addNSView(NSViewBasedPtr nsViewBased, CocoaShellPosition pos) {
    addTabTo(getTabViewForPosition(pos), nsViewBased);
}
void CocoaShell::removeNSView(NSViewBasedPtr nsViewBased, CocoaShellPosition pos) {
    removeTabFrom(getTabViewForPosition(pos), nsViewBased);
}

void CocoaShell::addNSToolbar(NSToolbar* nsToolbar) {
    [window setToolbar:nsToolbar];
}
void CocoaShell::removeNSToolbar(NSToolbar* nsToolbar) {
    [window setToolbar:nil];
}

void CocoaShell::initWindow() {
    this->window = [[NSWindow alloc] initWithContentRect:NSMakeRect(57, 601, 1200, 1000)
    styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
    backing:NSBackingStoreBuffered defer:NO];

    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    [window setTitle:@"Cocoa Window Title"];

    [window makeKeyAndOrderFront:nil];
}

void CocoaShell::initComponents() {
    initSplitter();
    initSideBarAreas();
    initCentralArea();
}

void CocoaShell::initSplitter() {
    horizontalSplitter = this->makeSplitView();
    verticalSplitter = this->makeSplitView();
    verticalSplitter.vertical = YES;
}

void CocoaShell::composeWindow() {
    [horizontalSplitter addSubview:centralArea];
    [horizontalSplitter addSubview:bottomSideBarArea];

    [verticalSplitter addSubview:leftSideBarArea];
    [verticalSplitter addSubview:horizontalSplitter];
    [verticalSplitter addSubview:rightSideBarArea];

    [[window contentView] addSubview:verticalSplitter];
}

NSSplitView* CocoaShell::makeSplitView() {
    NSSplitView* splitView = [[NSSplitView alloc] initWithFrame:this->getContentFrame()];
    splitView.dividerStyle = NSSplitViewDividerStyleThin;
    splitView.autoresizingMask = NSViewHeightSizable | NSViewWidthSizable;

    return splitView;
}

void CocoaShell::initSideBarAreas() {
    leftSideBarArea = makeTabView();
    rightSideBarArea = makeTabView();
    bottomSideBarArea = makeTabView();
}

void CocoaShell::initCentralArea() {
    centralArea = this->makeTabView();
    centralArea.frame = this->getContentFrame();
}

NSTabView* CocoaShell::makeTabView() {
    return [[NSTabView alloc] initWithFrame:getContentFrame()];
}

NSTabViewItem *CocoaShell::makeTabViewItem(NSViewBasedPtr nsViewBased) {
    NSTabViewItem* item = [[NSTabViewItem alloc] init];
    [item setView:nsViewBased->getNSView()];
    [item setLabel:[NSString stringWithUTF8String:nsViewBased->getTitle().c_str()]];

    return item;
}

NSRect CocoaShell::getContentFrame() {
    return [[window contentView] bounds];
}

void CocoaShell::updateTab(NSViewBasedPtr nsViewBased, CocoaShellPosition pos) {
    if(nsViewBased->getNSView().isHidden)
        removeTabFrom(getTabViewForPosition(pos), nsViewBased);
    else
        addTabTo(getTabViewForPosition(pos), nsViewBased);
}

void CocoaShell::removeTabFrom(NSTabView *tabView, NSViewBasedPtr nsViewBased) {
    NSArray* arr = [tabView tabViewItems];
    for(int i = 0; [arr count] ; i++) {
        NSTabViewItem* item = [arr objectAtIndex:i];
        if(item.view == nsViewBased->getNSView()) {
            [tabView removeTabViewItem:item];
            break;
        }
    };
    updateSideBarWidths();
}

void CocoaShell::addTabTo(NSTabView *tabView, NSViewBasedPtr nsViewBased) {
    NSTabViewItem* item = makeTabViewItem(nsViewBased);

    [tabView addTabViewItem: item];

    updateSideBarWidths();
}

NSTabView *CocoaShell::getTabViewForPosition(CocoaShellPosition pos) {
    if(pos == LEFT) return leftSideBarArea;
    if(pos == RIGHT) return rightSideBarArea;
    if(pos == BOTTOM) return bottomSideBarArea;
    else return centralArea;
}

void CocoaShell::updateSideBarWidths() {
    int left = ([getTabViewForPosition(LEFT) numberOfTabViewItems] > 0) ? 250 : 0;
    int right = ([getTabViewForPosition(RIGHT) numberOfTabViewItems] > 0) ? 250 : 0;
    int bottom = ([getTabViewForPosition(BOTTOM) numberOfTabViewItems] > 0) ? 250 : 0;

    [horizontalSplitter setPosition:getContentFrame().size.height-bottom ofDividerAtIndex:0];
    [verticalSplitter setPosition:left ofDividerAtIndex:0];
    [verticalSplitter setPosition:getContentFrame().size.width-right ofDividerAtIndex:1];
}

void CocoaShell::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

CocoaShellPtr CocoaShell::me() {
    return this->shared_from_this();
}

