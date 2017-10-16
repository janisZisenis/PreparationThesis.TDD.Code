#ifndef COCOAVIEWS_COCOASHELL_H
#define COCOAVIEWS_COCOASHELL_H

#include <memory>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include "CocoaViews/CocoaShell/CocoaShell.h"
#include <Foundation/Foundation.h>

enum CocoaShellPosition { LEFT, RIGHT, BOTTOM, CENTRAL };

class CNAcceptor;

@class NSView;
@class NSToolbar;
@class NSWindow;
@class NSTabView;
@class NSSplitView;
@class NSTabViewItem;

class CocoaShell;
typedef std::shared_ptr<CocoaShell> CocoaShellPtr;

class CocoaShell : public CNVisitable, public std::enable_shared_from_this<CocoaShell> {
public:
    static CocoaShellPtr getNewInstance();
    virtual ~CocoaShell();
private:
    CocoaShell();

public:
    virtual void addNSView(NSView* nsView, CocoaShellPosition pos);
    virtual void removeNSView(NSView* nsView, CocoaShellPosition pos);

    virtual void addNSToolbar(NSToolbar* nsToolbar);
    virtual void removeNSToolbar(NSToolbar* nsToolbar);

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual void updateTab(NSView* nsView, CocoaShellPosition pos);
    virtual void removeTabFrom(NSTabView* tabView, NSView* tab);
    virtual void addTabTo(NSTabView* tabView, NSView* tab);
    virtual NSTabView* getTabViewForPosition(CocoaShellPosition pos);

    virtual void initWindow();
    virtual void initComponents();
    virtual void initSplitter();
    virtual NSSplitView* makeSplitView();
    virtual void initSideBarAreas();
    virtual void initCentralArea();
    virtual NSTabView* makeTabView();
    virtual void composeWindow();
    virtual NSTabViewItem* makeTabViewItem(NSView* nsView);
    virtual NSRect getContentFrame();
    virtual void updateSideBarWidths();

private:
    CocoaShellPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    NSWindow* window;
    NSSplitView* horizontalSplitter;
    NSSplitView* verticalSplitter;

    NSTabView* centralArea;
    NSTabView* leftSideBarArea;
    NSTabView* rightSideBarArea;
    NSTabView* bottomSideBarArea;
};

#endif //COCOAVIEWS_COCOASHELL_H