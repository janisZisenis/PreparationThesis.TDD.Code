#ifndef COCOAVIEWS_COCOASOLUTIONEXPLORER_H
#define COCOAVIEWS_COCOASOLUTIONEXPLORER_H

#include <memory>
#include <string>
#include <CrossViews/CNSolutionExplorerPresenter/CNSolutionExplorerView.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>
#include "CocoaViews/NSViewBased/NSViewBased.h"

class CNAcceptor;

class CocoaSolutionItemFactory;

@class NSScrollView;
@class NSView;
@class NSOutlineView;
@class CocoaSolutionModel;
@class CocoaSolutionItem;

class CocoaSolutionExplorer;
typedef std::shared_ptr<CocoaSolutionExplorer> CocoaSolutionExplorerPtr;

class CocoaSolutionExplorer : public NSViewBased, public CNSolutionExplorerView, public std::enable_shared_from_this<CocoaSolutionExplorer> {
public:
    static CocoaSolutionExplorerPtr getNewInstance(std::shared_ptr<CocoaSolutionItemFactory> itemFactory);
    virtual ~CocoaSolutionExplorer();
private:
    CocoaSolutionExplorer(std::shared_ptr<CocoaSolutionItemFactory> itemFactory);

public:
    virtual NSView* getNSView() override;

    virtual std::string getTitle() override;
    virtual bool isVisible();
    virtual void toggleVisibility();

    virtual void removeIndex(const CNHierarchyIndex &index) override;
    virtual CNHierarchyIndex getSelectedIndex() override;
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) override;

    void accept(CNVisitorPtr visitor) override;
    virtual void setListener(std::shared_ptr<CNSolutionExplorerListener> listener) override;
private:
    CocoaSolutionItem* makeItem(CNVisitablePtr visitable);

    CocoaSolutionExplorerPtr me();
private:
    std::shared_ptr<CNAcceptor> acceptor;
    std::shared_ptr<CocoaSolutionItemFactory> itemFactory;

    std::shared_ptr<CNSolutionExplorerListener> listener;
    NSOutlineView* outlineView;
    NSScrollView* scrollView;

    CocoaSolutionModel* viewDataSource;
    std::string title;

private:
    virtual void onSelectionChanged();
};

#endif //COCOAVIEWS_COCOASOLUTIONEXPLORER_H