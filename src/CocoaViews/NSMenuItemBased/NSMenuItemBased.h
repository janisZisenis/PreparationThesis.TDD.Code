#ifndef COCOAVIEWS_NSMENUITEMBASED_H
#define COCOAVIEWS_NSMENUITEMBASED_H

#include <memory>

@class NSMenuItem;

class NSMenuItemBased;
typedef std::shared_ptr<NSMenuItemBased> NSMenuItemBasedPtr;
class NSMenuItemBased {
public:
    virtual ~NSMenuItemBased() {};
protected:
    NSMenuItemBased() {};

public:
    virtual NSMenuItem* getNSMenuItem() = 0;
};

#endif //COCOAVIEWS_NSMENUITEMBASED_H