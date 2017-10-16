#ifndef COCOAVIEWS_COCOASOLUTIONEXPLORER_H
#define COCOAVIEWS_COCOASOLUTIONEXPLORER_H

#include <memory>
#include <string>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include "CocoaModelIndex.h"

class CNAcceptor;

@class NSScrollView;
@class NSView;
@class NSOutlineView;
@class CocoaSolutionModel;
@class CocoaSolutionItem;

class CocoaSolutionExplorer;
typedef std::shared_ptr<CocoaSolutionExplorer> CocoaSolutionExplorerPtr;

class CocoaSolutionExplorer : public CNVisitable, public std::enable_shared_from_this<CocoaSolutionExplorer> {
public:
    static CocoaSolutionExplorerPtr getNewInstance();
    virtual ~CocoaSolutionExplorer();
private:
    CocoaSolutionExplorer();

public:
    virtual NSView* getNSView();

    virtual std::string getTitle();
    virtual bool isVisible();
    virtual void toggleVisibility();

    virtual void removeIndex(const CocoaModelIndex &index);
    virtual CocoaModelIndex getSelectedIndex();
    virtual void insertItem(CocoaSolutionItem* item, const CocoaModelIndex &index, int childPos);

    void accept(CNVisitorPtr visitor) override;

private:
    CocoaSolutionExplorerPtr me();
private:
    std::shared_ptr<CNAcceptor> acceptor;
    NSOutlineView* outlineView;
    NSScrollView* scrollView;

    CocoaSolutionModel* viewDataSource;
    std::string title;

private:
    virtual void onSelectionChanged();
};

#endif //COCOAVIEWS_COCOASOLUTIONEXPLORER_H