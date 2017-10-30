#ifndef COCOAVIEWS_COCOAMENU_H
#define COCOAVIEWS_COCOAMENU_H

#include <memory>
#include <string>
#include <CrossHierarchies/CNTagged/CNTagged.h>
#include <CrossViews/DynamicMenuPresenter/MenuView.h>
#include "CocoaViews/NSMenuItemBased/NSMenuItemBased.h"

class CNAcceptor;

@class NSMenuItem;
@class NSMenu;

class CocoaMenu;
typedef std::shared_ptr<CocoaMenu> CocoaMenuPtr;

class CocoaMenu : public NSMenuItemBased, public CNTagged, public MenuView, public std::enable_shared_from_this<CocoaMenu> {
public:
    static CocoaMenuPtr getNewInstance(std::string title);
    virtual ~CocoaMenu();
private:
    CocoaMenu(std::string title);

public:
    virtual NSMenuItem* getNSMenuItem() override;

    virtual void addNSMenuItem(NSMenuItemBasedPtr nsMenuItemBased);
    virtual void removeNSMenuItem(NSMenuItemBasedPtr nsMenuItemBased);

    virtual void accept(CNVisitorPtr visitor) override;

    virtual std::string getTag() override;
    virtual void setTag(std::string tag);

private:
    virtual void initializeEmptyMenuItem();
    virtual void initializeMenu();
    virtual void initializeMenuItem();

    virtual void disableAutoEnableMenuItems();

    virtual void addToMenu(NSMenuItem *menuItem);
    virtual void removeFromMenu(NSMenuItem *menuItem);

    virtual bool menuIsEmpty();
    virtual bool menuContainsEmptyMenuItem();
    virtual void addEmptyMenuItemToMenu();
    virtual void removeEmptyMenuItemFromMenu();
    
private:
    CocoaMenuPtr me();

private:
    std::shared_ptr<CNAcceptor> typeAcceptor;
    std::shared_ptr<CNAcceptor> tagAcceptor;
    std::string tag;

    NSMenuItem* menuItem;
    NSMenu* menu;
    NSMenuItem* emptyMenuItem;
};



#endif //COCOAVIEWS_COCOAMENU_H