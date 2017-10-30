#ifndef COCOAVIEWS_COCOAMENUBAR_H
#define COCOAVIEWS_COCOAMENUBAR_H

#include <Hierarchies/CNVisitable/CNVisitable.h>

class CNAcceptor;

class CocoaMenuBar;
@class NSMenu;
@class NSMenuItem;

class CocoaMenuBar;
typedef std::shared_ptr<CocoaMenuBar> CocoaMenuBarPtr;

class CocoaMenuBar : public CNVisitable, public std::enable_shared_from_this<CocoaMenuBar> {
public:
    static CocoaMenuBarPtr getNewInstance();
    virtual ~CocoaMenuBar();
private:
    CocoaMenuBar();

public:
    virtual NSMenu* getNSMenu();

public:
    virtual void addNSMenuItem(NSMenuItem* nsMenuItem);
    virtual void removeNSMenuItem(NSMenuItem* nsMenuItem);

    virtual void accept(CNVisitorPtr visitor) override;
private:
    CocoaMenuBarPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;
    NSMenu* menuBar;
};

#endif //COCOAVIEWS_COCOAMENUBAR_H