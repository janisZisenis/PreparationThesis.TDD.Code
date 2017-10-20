#include "CocoaSolutionModel.h"
#include "CocoaSolutionItem.h"

@implementation CocoaSolutionModel

- (instancetype) initWithNSOutlineView:(NSOutlineView*)view
{
    self = [super init];
self = [super init];
    if(self) {
        root = [[CocoaSolutionItem alloc] initWithName:@"root" type:@"root"];
        _nameIdentifier = @"Name";
        _typeIdentifier = @"Type";
        _view = view;

        NSTableColumn* nameColumn = [[NSTableColumn alloc] initWithIdentifier:_nameIdentifier];
        nameColumn.title = _nameIdentifier;
        [_view addTableColumn:nameColumn];
        [_view setOutlineTableColumn:nameColumn];

        NSTableColumn* typeColumn = [[NSTableColumn alloc] initWithIdentifier:_typeIdentifier];
        typeColumn.title = _typeIdentifier;
        [_view addTableColumn:typeColumn];

        [_view setRowHeight:20];
    }

    return self;
}

-(void)insertItem:(CocoaSolutionItem*)item atParentIndex:(const CNHierarchyIndex&)parentIndex atChildPos:(int)childPos{
    CocoaSolutionItem* parent = root;
    for(int i = 0; i < parentIndex.depth(); i++) {
        parent = [root getChildAt:parentIndex[i]];
    }

    [parent insertChild:item atChildPos:childPos];
    [_view reloadData];
}

-(void)removeItemAtParentIndex:(const CNHierarchyIndex&)parentIndex atChildPos:(int)childPos {
    CocoaSolutionItem* parent = root;
    for(int i = 0; i < parentIndex.depth(); i++) {
        parent = [root getChildAt:parentIndex[i]];
    }

    [parent removeChildAt:childPos];
    [_view reloadData];
}

- (boost::signals2::signal<void()>&) selectionChanged {
    return _selectionChanged;
}

- (id)outlineView:(NSOutlineView *)outlineView viewForTableColumn:(NSTableColumn *)tableColumn item:(id)item {
    if(item == nil) return nil;

    NSTextField *result = [_view makeViewWithIdentifier:tableColumn.identifier owner:self];

    if (result == nil) {
    result = [[NSTextField alloc] init];
    [result setBordered:NO];
    [result setBackgroundColor:[NSColor clearColor]];
    result.identifier = tableColumn.identifier;
}

    if([tableColumn.identifier isEqual:_nameIdentifier])
    result.stringValue = [item getName];
    else
    result.stringValue = [item getType];

    return result;
}


- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
    return (item == nil) ? [root getChildCount] : [item getChildCount];
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item {
    return (item == nil) ? [root getChildAt:index] : [item getChildAt:index];
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    return (item == nil) ? YES /*([root getChildCount] > 0)*/ : ([item getChildCount] > 0);
}

- (void)outlineViewSelectionDidChange:(NSNotification *)notification {
    _selectionChanged();
}


@end
