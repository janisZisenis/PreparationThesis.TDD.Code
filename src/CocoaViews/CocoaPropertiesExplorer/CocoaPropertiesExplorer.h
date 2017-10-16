#ifndef COCOALVIEWS_COCOAPROPERTIESEXPLORER_H
#define COCOALVIEWS_COCOAPROPERTIESEXPLORER_H

#include <memory>
#include <string>

@class NSView;
@class NSTableView;
@class NSScrollView;
@class CocoaPropertiesModel;

class CocoaPropertiesExplorer;
typedef std::shared_ptr<CocoaPropertiesExplorer> CocoaPropertiesExplorerViewImpPtr;

class CocoaPropertiesExplorer {
public:
    static CocoaPropertiesExplorerViewImpPtr getNewInstance();
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

    CocoaPropertiesModel* viewDataSource;
    NSTableView* tableView;
    NSScrollView* scrollView;
    std::string title;
};
#endif //COCOALVIEWS_COCOAPROPERTIESEXPLORER_H