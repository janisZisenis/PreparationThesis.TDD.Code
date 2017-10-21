#ifndef COCOAVIEWS_COCOASOLUTIONITEM_H
#define COCOAVIEWS_COCOASOLUTIONITEM_H

#import <Cocoa/Cocoa.h>
#include <vector>


@interface CocoaSolutionItem : NSObject {
    NSString* _name;
    NSString* _type;
    std::vector<CocoaSolutionItem*> _children;
    CocoaSolutionItem* _parent;
}

- (instancetype) initWithName:(NSString*)name type:(NSString*)type;

- (NSInteger) getChildCount;
- (CocoaSolutionItem*) getChildAt:(NSInteger)index;
- (void) insertChild:(CocoaSolutionItem*)item atChildPos:(NSInteger)childPos;
- (void) removeChildAt:(NSInteger)childPos;
- (NSString*) getName;
- (NSString*) getType;
- (CocoaSolutionItem*) getParent;
- (void) setParent:(CocoaSolutionItem*)parent;
- (NSInteger) childPosFor:(CocoaSolutionItem*)item;
- (NSInteger) getRow;

@end

#endif //COCOAVIEWS_COCOASOLUTIONMODEL_H