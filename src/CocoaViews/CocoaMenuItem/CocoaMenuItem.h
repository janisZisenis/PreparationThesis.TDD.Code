#ifndef COCOAVIEWS_COCOAMENUITEM_H
#define COCOAVIEWS_COCOAMENUITEM_H

#include <string>
#include "CocoaViews/CocoaActionListener/CocoaTarget.h"

@class NSMenuItem;

class CocoaMenuItem;
typedef std::shared_ptr<CocoaMenuItem> CocoaMenuItemPtr;

class CocoaMenuItem : public CocoaTarget {
public:
    static CocoaMenuItemPtr getNewInstance();
    virtual ~CocoaMenuItem();
private:
    CocoaMenuItem();

public:
    virtual NSMenuItem* getNSMenuItem();

    virtual void setTitle(std::string newTitle);
    virtual void setAccessibility(bool newAccessibility);
    virtual void setChecked(bool checked);

private:
    virtual void connectToMenuItem();

    NSMenuItem* menuItem;
    CocoaActionListener* clickedAction;

private:
    virtual void onAction(NSObject *object, CocoaActionListener *action);

};

#endif //COCOAVIEWS_COCOAMENUITEM_H