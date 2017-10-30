#ifndef CROSSVIEWS_PROPERTIESEXPLORERPRESENTER_H
#define CROSSVIEWS_PROPERTIESEXPLORERPRESENTER_H

#include <Base/CNObserver/CNObserver.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>

class PropertiesExplorerView;
class HierarchicModelAccess;
class SelectionModel;

class PropertiesExplorerPresenter;
typedef std::shared_ptr<PropertiesExplorerPresenter> PropertiesExplorerPresenterPtr;

class PropertiesExplorerPresenter : public virtual CNVisitable, public CNObserver {
public:
    static PropertiesExplorerPresenterPtr getNewInstance(std::shared_ptr<PropertiesExplorerView> view,
                                                         std::shared_ptr<HierarchicModelAccess> modelAccess,
                                                         std::shared_ptr<SelectionModel> selectionModel);
    virtual ~PropertiesExplorerPresenter();
private:
    PropertiesExplorerPresenter(std::shared_ptr<PropertiesExplorerView> view,
                                std::shared_ptr<HierarchicModelAccess> modelAccess,
                                std::shared_ptr<SelectionModel> selectionModel);

public:
    virtual void accept(CNVisitorPtr visitor) override;
    virtual void update() override;

private:
    virtual void clearProperties();
    virtual void displayProperties();

private:
    std::shared_ptr<PropertiesExplorerView> view;
    std::shared_ptr<HierarchicModelAccess> modelAccess;
    std::shared_ptr<SelectionModel> selectionModel;
};

#endif //CROSSVIEWS_PROPERTIESEXPLORERPRESENTER_H