#ifndef COCOALVIEWS_COCOAPROPERTIESEXPLORER_H
#define COCOALVIEWS_COCOAPROPERTIESEXPLORER_H

#include <memory>
#include <string>
#include <CrossNative/CNVisitable/CNVisitable.h>

class CNAcceptor;

@class NSView;
@class NSTableView;
@class NSScrollView;
@class CocoaPropertiesModel;

class CocoaPropertiesExplorer;
typedef std::shared_ptr<CocoaPropertiesExplorer> CocoaPropertiesExplorerPtr;

class CocoaPropertiesExplorer : public CNVisitable, public std::enable_shared_from_this<CocoaPropertiesExplorer> {
public:
    static CocoaPropertiesExplorerPtr getNewInstance();
    virtual ~CocoaPropertiesExplorer();
private:
    CocoaPropertiesExplorer();

public:
    virtual NSView* getNSView();

    virtual std::string getTitle();
    virtual bool isVisible();
    virtual void toggleGUIVisibility();

    virtual void displayProperties(CocoaPropertiesModel* model);
    virtual void displayEmptyProperties();

    virtual void accept(CNVisitorPtr visitor) override;

private:
    CocoaPropertiesExplorerPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    CocoaPropertiesModel* viewDataSource;
    NSTableView* tableView;
    NSScrollView* scrollView;
    std::string title;
};
#endif //COCOALVIEWS_COCOAPROPERTIESEXPLORER_H