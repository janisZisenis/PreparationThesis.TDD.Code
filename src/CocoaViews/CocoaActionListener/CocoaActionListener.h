#import <Cocoa/Cocoa.h>

class CocoaTarget;

@interface CocoaActionListener : NSObject {
    CocoaTarget* _target;
}

- (instancetype) initWithTarget:(CocoaTarget*)target;
- (void)listen:(id)sender;

@end
