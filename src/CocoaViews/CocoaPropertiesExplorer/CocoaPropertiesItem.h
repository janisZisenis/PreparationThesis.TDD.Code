#ifndef COCOALVIEWS_COCOAPROPERTIESITEM_H
#define COCOALVIEWS_COCOAPROPERTIESITEM_H

#import <Cocoa/Cocoa.h>
#include <string>

@interface CocoaPropertiesItem : NSObject {
    std::string _property;
    std::string _value;
}

- (instancetype) initWithProperty:(std::string)property value:(std::string)value;

- (std::string) getProperty;
- (std::string) getValue;

@end

#endif //COCOALVIEWS_COCOAPROPERTIESITEM_H