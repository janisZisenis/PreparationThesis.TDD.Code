#include "CocoaPropertiesItem.h"

@implementation CocoaPropertiesItem

- (instancetype) initWithProperty:(std::string)property value:(std::string)value
{
    self = [super init];
    if(self) {
        _property = property;
        _value = value;
    }

    return self;
}

- (std::string) getProperty {
    return _property;
};

- (std::string) getValue {
    return _value;
};

@end
