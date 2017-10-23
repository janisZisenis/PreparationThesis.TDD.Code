#include "CocoaPropertiesExplorer.h"
#include "CocoaPropertiesExplorerVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#import <Cocoa/Cocoa.h>
#include <CrossNative/CNVisitor/CNVisitor.h>
#import "CocoaPropertiesModel.h"
#import "CocoaPropertiesItem.h"
#include "CocoaPropertiesModelFactory.h"

CocoaPropertiesExplorerPtr CocoaPropertiesExplorer::getNewInstance(CocoaPropertiesModelFactoryPtr modelFactory)  {
    return CocoaPropertiesExplorerPtr(new CocoaPropertiesExplorer(modelFactory));
}

CocoaPropertiesExplorer::~CocoaPropertiesExplorer() {}

CocoaPropertiesExplorer::CocoaPropertiesExplorer(CocoaPropertiesModelFactoryPtr modelFactory)
        : acceptor(CNAcceptorImp<CocoaPropertiesExplorerVisitor, CocoaPropertiesExplorer>::getNewInstance()),
          modelFactory(modelFactory),
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

void CocoaPropertiesExplorer::displayPropertiesFor(CNVisitablePtr visitable) {
    [tableView setDataSource:nil];
    [tableView setDelegate:nil];

    viewDataSource = makePropertiesModel(visitable);

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

CocoaPropertiesModel *CocoaPropertiesExplorer::makePropertiesModel(CNVisitablePtr visitable) {
    return modelFactory->makeCocoaPropertiesModel(visitable);
}

