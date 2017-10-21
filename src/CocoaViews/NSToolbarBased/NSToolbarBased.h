#ifndef COCOAVIEWS_NSTOOLBARBASED_H
#define COCOAVIEWS_NSTOOLBARBASED_H

#include <memory>
#include <string>

@class NSToolbar;

class NSToolbarBased;
typedef std::shared_ptr<NSToolbarBased> NSToolbarBasedPtr;
class NSToolbarBased {
public:
    virtual ~NSToolbarBased() {};
protected:
    NSToolbarBased() {};

public:
    virtual NSToolbar* getNSToolbar() = 0;
};

#endif //COCOAVIEWS_NSTOOLBARBASED_H