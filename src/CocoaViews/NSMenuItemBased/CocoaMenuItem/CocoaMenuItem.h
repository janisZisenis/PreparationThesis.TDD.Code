#ifndef COCOAVIEWS_COCOAMENUITEM_H
#define COCOAVIEWS_COCOAMENUITEM_H

#include <string>
#include <CrossViews/MenuEntryPresenter/MenuEntryView.h>
#include "CocoaViews/CocoaActionListener/CocoaTarget.h"
#include "CocoaViews/NSMenuItemBased/NSMenuItemBased.h"
#import <Cocoa/Cocoa.h>

class CNAcceptor;

@class NSMenuItem;

class CocoaMenuItem;
typedef std::shared_ptr<CocoaMenuItem> CocoaMenuItemPtr;

class CocoaMenuItem : public CocoaTarget, public NSMenuItemBased, public MenuEntryView, public std::enable_shared_from_this<CocoaMenuItem> {
public:
    static CocoaMenuItemPtr getNewInstance();
    virtual ~CocoaMenuItem();
private:
    CocoaMenuItem();

public:
    virtual NSMenuItem* getNSMenuItem() override;

    virtual void setTitle(std::string) override;
    virtual void check() override;
    virtual void uncheck() override;
    virtual void enable() override;
    virtual void disable() override;

    void accept(CNVisitorPtr visitor) override;
    virtual void setListener(std::shared_ptr<MenuEntryListener> listener) override;

private:
    virtual void connectToMenuItem();
    virtual void setState(const NSControlStateValue state);
    virtual void setMenuEnabled(bool enabled);

    CocoaMenuItemPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;
    std::shared_ptr<MenuEntryListener> listener;

    std::string title;

    NSMenuItem* menuItem;
    CocoaActionListener* clickedAction;

private:
    virtual void onAction(NSObject *object, CocoaActionListener *action) override;
};

#endif //COCOAVIEWS_COCOAMENUITEM_H