#ifndef CROSSVIEWS_PROPERTIESEXPLORERPRESENTER_H
#define CROSSVIEWS_PROPERTIESEXPLORERPRESENTER_H

#include <CrossNative/CNVisitable/CNVisitable.h>

class PropertiesExplorerView;
class SelectionModel;

class PropertiesExplorerPresenter;
typedef std::shared_ptr<PropertiesExplorerPresenter> PropertiesExplorerPresenterPtr;

class PropertiesExplorerPresenter : public virtual CNVisitable {
public:
    static PropertiesExplorerPresenterPtr getNewInstance(std::shared_ptr<PropertiesExplorerView> view);
    virtual ~PropertiesExplorerPresenter();
private:
    PropertiesExplorerPresenter(std::shared_ptr<PropertiesExplorerView> view);

public:
    virtual void accept(CNVisitorPtr visitor) override;

private:
    std::shared_ptr<PropertiesExplorerView> view;
};

#endif //CROSSVIEWS_PROPERTIESEXPLORERPRESENTER_H