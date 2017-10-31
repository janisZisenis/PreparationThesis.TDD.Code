#ifndef CROSSNATIVE_PROPERTIESEXPLORERPRESENTER_H
#define CROSSNATIVE_PROPERTIESEXPLORERPRESENTER_H

#include <Base/CNObserver/CNObserver.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>

class CNPropertiesExplorerView;
class CNHierarchicComponentAccess;
class CNSelectionModel;

class CNPropertiesExplorerPresenter;
typedef std::shared_ptr<CNPropertiesExplorerPresenter> CNPropertiesExplorerPresenterPtr;

class CNPropertiesExplorerPresenter : public virtual CNVisitable, public CNObserver {
public:
    static CNPropertiesExplorerPresenterPtr getNewInstance(std::shared_ptr<CNPropertiesExplorerView> view,
                                                           std::shared_ptr<CNHierarchicComponentAccess> modelAccess,
                                                           std::shared_ptr<CNSelectionModel> selectionModel);
    virtual ~CNPropertiesExplorerPresenter();
private:
    CNPropertiesExplorerPresenter(std::shared_ptr<CNPropertiesExplorerView> view,
                                  std::shared_ptr<CNHierarchicComponentAccess> modelAccess,
                                  std::shared_ptr<CNSelectionModel> selectionModel);

public:
    virtual void accept(CNVisitorPtr visitor) override;
    virtual void update() override;

private:
    virtual void clearProperties();
    virtual void displayProperties();

private:
    std::shared_ptr<CNPropertiesExplorerView> view;
    std::shared_ptr<CNHierarchicComponentAccess> modelAccess;
    std::shared_ptr<CNSelectionModel> selectionModel;
};

#endif //CROSSNATIVE_PROPERTIESEXPLORERPRESENTER_H