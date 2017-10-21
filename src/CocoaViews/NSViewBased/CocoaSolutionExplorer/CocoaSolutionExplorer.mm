#include "CocoaSolutionExplorer.h"
#include "CocoaSolutionExplorerVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#import "CocoaSolutionModel.h"
#import "CocoaSolutionItem.h"

CocoaSolutionExplorerPtr CocoaSolutionExplorer::getNewInstance()  {
    return CocoaSolutionExplorerPtr(new CocoaSolutionExplorer());
}
CocoaSolutionExplorer::~CocoaSolutionExplorer() {}
CocoaSolutionExplorer::CocoaSolutionExplorer()
        : acceptor(CNAcceptorImp<CocoaSolutionExplorerVisitor, CocoaSolutionExplorer>::getNewInstance()),
          title("Solution Explorer") {
    outlineView = [NSOutlineView new];
    viewDataSource = [[CocoaSolutionModel alloc] initWithNSOutlineView:outlineView];

    [outlineView setDelegate: viewDataSource];
    [outlineView setDataSource: viewDataSource];

    [viewDataSource selectionChanged].connect(boost::bind(&CocoaSolutionExplorer::onSelectionChanged, this));

    scrollView = [NSScrollView new];
    [scrollView setHasHorizontalScroller:YES];
    [scrollView setHasVerticalScroller:YES];

    [scrollView setDocumentView:outlineView];
}

NSView* CocoaSolutionExplorer::getNSView() {
    return this->scrollView;
}

std::string CocoaSolutionExplorer::getTitle() {
    return title;
}

bool CocoaSolutionExplorer::isVisible() {
    return !scrollView.isHidden;
}

void CocoaSolutionExplorer::toggleVisibility() {
    [scrollView setHidden: !scrollView.isHidden];
}

void CocoaSolutionExplorer::removeIndex(const CNHierarchyIndex &index) {
    [outlineView selectRowIndexes:[NSIndexSet indexSet] byExtendingSelection:NO];
    [viewDataSource removeItemAtParentIndex:index.parent() atChildPos:index.childPosition()];
    [outlineView selectRowIndexes:[NSIndexSet indexSetWithIndex:index.childPosition()] byExtendingSelection:NO];
}

CNHierarchyIndex CocoaSolutionExplorer::getSelectedIndex() {
    CocoaSolutionItem* item = [outlineView itemAtRow:[outlineView selectedRow]];

    std::vector<int> path;
    while([item getParent] != nil) {
        path.insert(path.begin(), [item getRow]);
        item = [item getParent];
    }
    return CNHierarchyIndex(path);
}

void CocoaSolutionExplorer::insertItem(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) {
    [viewDataSource insertItem:makeItem(visitable) atParentIndex:index atChildPos:childPos];
}

void CocoaSolutionExplorer::onSelectionChanged() {}

void CocoaSolutionExplorer::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

CocoaSolutionExplorerPtr CocoaSolutionExplorer::me() {
    return this->shared_from_this();
}

CocoaSolutionItem *CocoaSolutionExplorer::makeItem(CNVisitablePtr visitable) {
    throw std::logic_error("Function not yet implemented");
    return nullptr;
}


