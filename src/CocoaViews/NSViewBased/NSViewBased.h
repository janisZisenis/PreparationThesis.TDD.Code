#ifndef COCOAVIEWS_NSVIEWBASED_H
#define COCOAVIEWS_NSVIEWBASED_H

#include <memory>
#include <string>

@class NSView;

class NSViewBased;
typedef std::shared_ptr<NSViewBased> NSViewBasedPtr;
class NSViewBased {
public:
    virtual ~NSViewBased() {};
protected:
    NSViewBased() {};

public:
    virtual NSView* getNSView() = 0;
    virtual std::string getTitle() = 0;
};

#endif //COCOAVIEWS_NSVIEWBASED_H