#ifndef COCOAVIEWS_COCOASOLUTIONMODEL_H
#define COCOAVIEWS_COCOASOLUTIONMODEL_H

#import <Cocoa/Cocoa.h>
#include <memory>
#include <boost/signals2/signal.hpp>
#include "CocoaModelIndex.h"

@class CocoaSolutionItem;
@class NSOutlineView;

@interface CocoaSolutionModel : NSObject <NSOutlineViewDataSource, NSOutlineViewDelegate> {
    CocoaSolutionItem* root;
    NSString* _nameIdentifier;
    NSString* _typeIdentifier;
    NSOutlineView* _view;
    boost::signals2::signal<void()> _selectionChanged;
}

- (instancetype) initWithNSOutlineView:(NSOutlineView*)view;

-(void)insertItem:(CocoaSolutionItem*)item atParentIndex:(const CocoaModelIndex&)parentIndex atChildPos:(int)childPos;

-(void)removeItemAtParentIndex:(const CocoaModelIndex&)parentIndex atChildPos:(int)childPos;

- (boost::signals2::signal<void()>&) selectionChanged;

- (id)outlineView:(NSOutlineView *)outlineView viewForTableColumn:(NSTableColumn *)tableColumn item:(id)item;

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item;

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item;

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item;

- (void)outlineViewSelectionDidChange:(NSNotification *)notification;

@end

#endif //COCOAVIEWS_COCOASOLUTIONMODEL_H