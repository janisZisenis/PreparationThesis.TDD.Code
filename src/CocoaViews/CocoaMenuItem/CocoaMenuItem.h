#ifndef COCOAVIEWS_COCOAMENUITEM_H
#define COCOAVIEWS_COCOAMENUITEM_H

#include <string>
#include <CrossViews/MenuEntryPresenter/MenuEntryView.h>
#include "CocoaViews/CocoaActionListener/CocoaTarget.h"
#import <Cocoa/Cocoa.h>

class CNAcceptor;

class CocoaMenuItem;
typedef std::shared_ptr<CocoaMenuItem> CocoaMenuItemPtr;

class CocoaMenuItem : public CocoaTarget, public MenuEntryView, public std::enable_shared_from_this<CocoaMenuItem> {
public:
    static CocoaMenuItemPtr getNewInstance();
    virtual ~CocoaMenuItem();
private:
    CocoaMenuItem();

public:
    virtual NSMenuItem* getNSMenuItem();

    virtual void setTitle(std::string newTitle) override;
    virtual void check() override;
    virtual void uncheck() override;
    virtual void enable() override;
    virtual void disable() override;

    void accept(CNVisitorPtr visitor) override;

private:
    virtual void connectToMenuItem();
    virtual void setState(const NSControlStateValue state);
    virtual void setEnabled(bool enabled);

    CocoaMenuItemPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    NSMenuItem* menuItem;
    CocoaActionListener* clickedAction;

private:
    virtual void onAction(NSObject *object, CocoaActionListener *action) override;
};

#endif //COCOAVIEWS_COCOAMENUITEM_H