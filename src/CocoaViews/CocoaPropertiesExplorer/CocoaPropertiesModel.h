#import <Cocoa/Cocoa.h>
#include <memory>

@class CocoaPropertiesItem;
class CocoaPropertiesExplorer;

@interface CocoaPropertiesModel : NSObject <NSTableViewDataSource, NSTableViewDelegate> {
    NSMutableArray* _objects;
    NSTableView* _view;
    NSString* _propertyIdentifier;
    NSString* _valueIdentifier;
}

- (instancetype) initWithTableView:(NSTableView*)view;

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

- (void)addItem:(CocoaPropertiesItem*)item;

@end
