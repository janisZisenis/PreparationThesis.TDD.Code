#ifndef COCOAVIEWS_COCOASHELL_H
#define COCOAVIEWS_COCOASHELL_H

#include <memory>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include "CocoaShell.h"
#include <Foundation/Foundation.h>

class CNAcceptor;

class NSViewBased;

@class NSView;
@class NSToolbar;
@class NSWindow;
@class NSTabView;
@class NSSplitView;
@class NSTabViewItem;

enum CocoaShellPosition { LEFT, RIGHT, BOTTOM, CENTRAL };

class CocoaShell;
typedef std::shared_ptr<CocoaShell> CocoaShellPtr;

class CocoaShell : public CNVisitable, public std::enable_shared_from_this<CocoaShell> {
public:
    static CocoaShellPtr getNewInstance();
    virtual ~CocoaShell();
private:
    CocoaShell();

public:
    virtual void addNSView(std::shared_ptr<NSViewBased> nsViewBased, CocoaShellPosition pos);
    virtual void removeNSView(std::shared_ptr<NSViewBased> nsViewBased, CocoaShellPosition pos);

    virtual void addNSToolbar(NSToolbar* nsToolbar);
    virtual void removeNSToolbar(NSToolbar* nsToolbar);

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual void updateTab(std::shared_ptr<NSViewBased> nsViewBased, CocoaShellPosition pos);
    virtual void removeTabFrom(NSTabView* tabView, std::shared_ptr<NSViewBased> nsViewBased);
    virtual void addTabTo(NSTabView* tabView, std::shared_ptr<NSViewBased> nsViewBased);
    virtual NSTabView* getTabViewForPosition(CocoaShellPosition pos);

    virtual void initWindow();
    virtual void initComponents();
    virtual void initSplitter();
    virtual NSSplitView* makeSplitView();
    virtual void initSideBarAreas();
    virtual void initCentralArea();
    virtual NSTabView* makeTabView();
    virtual void composeWindow();
    virtual NSTabViewItem* makeTabViewItem(std::shared_ptr<NSViewBased> nsViewBased);
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