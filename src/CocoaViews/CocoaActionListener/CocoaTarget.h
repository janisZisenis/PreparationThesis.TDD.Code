#ifndef COCOAVIEWS_COCOATARGET_H
#define COCOAVIEWS_COCOATARGET_H

@class NSObject;
@class CocoaActionListener;

class CocoaTarget{
public:
    virtual ~CocoaTarget() {};
protected:
    CocoaTarget() {}

public:
    virtual void onAction(NSObject *object, CocoaActionListener *action) = 0;
};

#endif //COCOAVIEWS_COCOATARGET_H
