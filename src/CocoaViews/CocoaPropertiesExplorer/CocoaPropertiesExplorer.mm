#include "CocoaPropertiesExplorer.h"
#include "CocoaPropertiesExplorerVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#import <Cocoa/Cocoa.h>
#include <CrossNative/CNVisitor/CNVisitor.h>
#import "CocoaPropertiesModel.h"
#import "CocoaPropertiesItem.h"

CocoaPropertiesExplorerPtr CocoaPropertiesExplorer::getNewInstance()  {
    return CocoaPropertiesExplorerPtr(new CocoaPropertiesExplorer());
}

CocoaPropertiesExplorer::~CocoaPropertiesExplorer() {}

CocoaPropertiesExplorer::CocoaPropertiesExplorer()
        : acceptor(CNAcceptorImp<CocoaPropertiesExplorerVisitor, CocoaPropertiesExplorer>::getNewInstance()),
          title("Properties Explorer") {
    tableView = [NSTableView new];

    NSTableColumn* propertyColumn = [[NSTableColumn alloc] initWithIdentifier:@"Property"];
    propertyColumn.title = @"Property";
    [tableView addTableColumn:propertyColumn];

    NSTableColumn* valueColumn = [[NSTableColumn alloc] initWithIdentifier:@"Value"];
    valueColumn.title = @"Value";
    [tableView addTableColumn:valueColumn];

    viewDataSource = [[CocoaPropertiesModel alloc] initWithTableView:tableView];

    [tableView setDataSource:viewDataSource];
    [tableView setDelegate:viewDataSource];

    scrollView = [NSScrollView new];
    [scrollView setHasHorizontalScroller:YES];
    [scrollView setHasVerticalScroller:YES];

    [scrollView setDocumentView:tableView];
}

NSView* CocoaPropertiesExplorer::getNSView() {
    return this->scrollView;
}

std::string CocoaPropertiesExplorer::getTitle() {
    return title;
}

bool CocoaPropertiesExplorer::isVisible() {
    return !scrollView.isHidden;
}

void CocoaPropertiesExplorer::toggleGUIVisibility() {
    [scrollView setHidden: !scrollView.isHidden];
}

void CocoaPropertiesExplorer::displayProperties(CocoaPropertiesModel* model) {
    [tableView setDataSource:nil];
    [tableView setDelegate:nil];

    viewDataSource = model;

    [tableView setDataSource:viewDataSource];
    [tableView setDelegate:viewDataSource];
}

void CocoaPropertiesExplorer::displayEmptyProperties() {
    [tableView setDataSource:nil];
    [tableView setDelegate:nil];

    viewDataSource = [[CocoaPropertiesModel alloc] initWithTableView:tableView];

    [tableView setDataSource:viewDataSource];
    [tableView setDelegate:viewDataSource];
}

void CocoaPropertiesExplorer::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

CocoaPropertiesExplorerPtr CocoaPropertiesExplorer::me() {
    return this->shared_from_this();
}

