#ifndef COCOALVIEWS_COCOAPROPERTIESEXPLORER_H
#define COCOALVIEWS_COCOAPROPERTIESEXPLORER_H

#include <memory>
#include <string>
#include "CrossViews/PropertiesExplorerPresenter/PropertiesExplorerView.h"
#include "CocoaViews/NSViewBased/NSViewBased.h"

class CNAcceptor;

@class NSView;
@class NSTableView;
@class NSScrollView;
@class CocoaPropertiesModel;

class CocoaPropertiesExplorer;
typedef std::shared_ptr<CocoaPropertiesExplorer> CocoaPropertiesExplorerPtr;

class CocoaPropertiesExplorer : public NSViewBased, public PropertiesExplorerView, public std::enable_shared_from_this<CocoaPropertiesExplorer> {
public:
    static CocoaPropertiesExplorerPtr getNewInstance();
    virtual ~CocoaPropertiesExplorer();
private:
    CocoaPropertiesExplorer();

public:
    virtual NSView* getNSView() override;
    virtual std::string getTitle() override;

    virtual void displayPropertiesFor(CNVisitablePtr visitable) override;
    virtual void displayEmptyProperties() override;

    virtual void accept(CNVisitorPtr visitor) override;

private:
    virtual CocoaPropertiesModel* makePropertiesModel(CNVisitablePtr visitable);

    CocoaPropertiesExplorerPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    CocoaPropertiesModel* viewDataSource;
    NSTableView* tableView;
    NSScrollView* scrollView;
    std::string title;
};
#endif //COCOALVIEWS_COCOAPROPERTIESEXPLORER_H