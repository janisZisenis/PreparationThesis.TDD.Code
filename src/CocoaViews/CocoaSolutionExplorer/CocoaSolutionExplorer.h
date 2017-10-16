#ifndef COCOAVIEWS_COCOASOLUTIONEXPLORER_H
#define COCOAVIEWS_COCOASOLUTIONEXPLORER_H

#include <memory>
#include <string>
#include "CocoaModelIndex.h"

@class NSScrollView;
@class NSView;
@class NSOutlineView;
@class CocoaSolutionModel;
@class CocoaSolutionItem;

class CocoaSolutionExplorer;
typedef std::shared_ptr<CocoaSolutionExplorer> CocoaSolutionExplorerPtr;

class CocoaSolutionExplorer {
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

    virtual void removeIndex(CocoaModelIndex index);
    virtual CocoaModelIndex getSelectedIndex();
    virtual void insertItem(CocoaSolutionItem* item, CocoaModelIndex index, int childPos);

private:
    virtual void onSelectionChanged();
private:

    NSOutlineView* outlineView;
    NSScrollView* scrollView;

    CocoaSolutionModel* viewDataSource;
    std::string title;
};

#endif //COCOAVIEWS_COCOASOLUTIONEXPLORER_H