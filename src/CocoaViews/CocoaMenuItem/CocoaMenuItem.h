#ifndef COCOAVIEWS_COCOAMENUITEM_H
#define COCOAVIEWS_COCOAMENUITEM_H

#include <CrossNative/CNVisitable/CNVisitable.h>
#include <string>
#include "CocoaViews/CocoaActionListener/CocoaTarget.h"

class CNAcceptor;

@class NSMenuItem;

class CocoaMenuItem;
typedef std::shared_ptr<CocoaMenuItem> CocoaMenuItemPtr;

class CocoaMenuItem : public CocoaTarget, public CNVisitable, public std::enable_shared_from_this<CocoaMenuItem> {
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

    void accept(CNVisitorPtr visitor) override;

private:
    CocoaMenuItemPtr me();
    virtual void connectToMenuItem();

private:
    std::shared_ptr<CNAcceptor> acceptor;
    
    NSMenuItem* menuItem;
    CocoaActionListener* clickedAction;

private:
    virtual void onAction(NSObject *object, CocoaActionListener *action) override;

};

#endif //COCOAVIEWS_COCOAMENUITEM_H