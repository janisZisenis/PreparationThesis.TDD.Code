#include "CocoaPropertiesModel.h"
#include "CocoaPropertiesItem.h"
#include "CocoaPropertiesExplorer.h"

@implementation CocoaPropertiesModel

- (instancetype) initWithTableView:(NSTableView*)view {
    self = [super init];
    if(self) {
        _propertyIdentifier = @"Property";
        _valueIdentifier = @"Value";
        _view = view;
        _objects = [[NSMutableArray alloc] init];
        [_view setRowHeight:20];
    }

    return self;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return [_objects count];
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    NSTextField *result = [_view makeViewWithIdentifier:tableColumn.identifier owner:self];

    if (result == nil) {
        result = [[NSTextField alloc] init];
        result.identifier = tableColumn.identifier;
        [result setBordered:NO];
        [result setBackgroundColor:[NSColor clearColor]];
    }

    if([tableColumn.identifier isEqual:_propertyIdentifier]) {
        result.stringValue = [NSString stringWithUTF8String:[[_objects objectAtIndex:row] getProperty].c_str()];
    }
    else {
        result.stringValue = [NSString stringWithUTF8String:[[_objects objectAtIndex:row] getValue].c_str()];
    }
    return result;

}

- (void)addItem:(CocoaPropertiesItem*)item {
    [_objects addObject:item];
    [_view reloadData];
}

- (void)deleteRow:(NSInteger)row {
    if(row < [_objects count]) {
        [_objects removeObjectAtIndex:row];
        [_view reloadData];
    }
}

@end
