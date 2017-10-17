#ifndef COCOAVIEWS_COCOAMENU_H
#define COCOAVIEWS_COCOAMENU_H

#include <memory>
#include <string>
#include <CrossNative/CNVisitable/CNVisitable.h>

class CNAcceptor;

@class NSMenuItem;
@class NSMenu;

class CocoaMenu;
typedef std::shared_ptr<CocoaMenu> CocoaMenuPtr;

class CocoaMenu : public CNVisitable, public std::enable_shared_from_this<CocoaMenu> {
public:
    static CocoaMenuPtr getNewInstance(std::string title);
    virtual ~CocoaMenu();
private:
    CocoaMenu(std::string title);

public:
    virtual NSMenuItem* getNSMenuItem();

    virtual void addNSMenuItem(NSMenuItem* menuItem);
    virtual void removeNSMenuItem(NSMenuItem* menuItem);

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual void initializeEmptyMenuItem();
    virtual void initializeMenu();
    virtual void initializeMenuItem();

    virtual void addToMenu(NSMenuItem *menuItem);
    virtual void removeFromMenu(NSMenuItem *menuItem);

    virtual bool menuIsEmpty();
    virtual bool menuContainsEmptyMenuItem();
    virtual void addEmptyMenuItemToMenu();
    virtual void removeEmptyMenuItemFromMenu();
    
private:
    CocoaMenuPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    NSMenuItem* menuItem;
    NSMenu* menu;
    NSMenuItem* emptyMenuItem;
};



#endif //COCOAVIEWS_COCOAMENU_H