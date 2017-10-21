#import "CocoaSolutionItem.h"

@implementation CocoaSolutionItem

- (instancetype) initWithName:(NSString*)name type:(NSString*)type
{
    self = [super init];
    if(self) {
    _name = name;
    _type = type;
    }

    return self;
}

- (NSInteger) getChildCount {
    return _children.size();
}

- (CocoaSolutionItem*) getChildAt:(NSInteger)index {
    return _children[index];
}

- (void) insertChild:(CocoaSolutionItem*)item atChildPos:(NSInteger)childPos {
    _children.insert(_children.begin() + childPos, item);
    [item setParent:self];
}

- (void) removeChildAt:(NSInteger)childPos {
    [_children[childPos] setParent:nil];
    _children.erase(_children.begin() + childPos);
}

- (NSString*) getName {
    return _name;
};

- (NSString*) getType {
    return _type;
};

- (void) setParent:(CocoaSolutionItem*)parent {
_parent = parent;
}

- (CocoaSolutionItem*) getParent {
    return _parent;
}

- (NSInteger) childPosFor:(CocoaSolutionItem*)item {
    NSInteger pos = (NSInteger) (std::find(_children.begin(), _children.end(), item) - _children.begin());
    return (pos >= [self getChildCount]) ? -1 : pos;
}

- (NSInteger) getRow {
    if (![self getParent]) return -1;

    return [[self getParent] childPosFor:self];
}

@end
