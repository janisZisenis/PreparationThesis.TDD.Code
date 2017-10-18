#import "CocoaActionListener.h"
#include "CocoaTarget.h"

@implementation CocoaActionListener

- (instancetype) initWithTarget:(CocoaTarget*)target
{
    self = [super init];
    if(self)
        _target = target;

    return self;
}

- (void) listen:(id)sender {
    _target->onAction(sender, self);
}

@end
