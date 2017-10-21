#ifndef CROSSVIEWS_HIERARCHICMODEL_H
#define CROSSVIEWS_HIERARCHICMODEL_H

#include "CrossViews/HierarchicModel/API/AddingHierarchicModel.h"
#include "CrossViews/HierarchicModel/API/InsertingHierarchicModel.h"
#include "CrossViews/HierarchicModel/API/HierarchicModelAccess.h"

class CNVisitable;
class CNComponent;
class CNHierarchy;

class HierarchicModelListener;

class HierarchicModel;
typedef std::shared_ptr<HierarchicModel> HierarchicModelPtr;

class HierarchicModel : public AddingHierarchicModel, public InsertingHierarchicModel, public HierarchicModelAccess {
public:
    static HierarchicModelPtr getNewInstance();
    virtual ~HierarchicModel();
protected:
    HierarchicModel();

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override;
    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override;

    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent, int childPos) override;
    virtual void remove(const CNHierarchyIndex& parent, int childPos) override;

    virtual void notifyInserted(std::shared_ptr<CNVisitable> visitable, const CNHierarchyIndex& parent, int childPos);
    virtual void notifyRemoved(const CNHierarchyIndex& parent);

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& parent) override;

    virtual void attach(std::shared_ptr<HierarchicModelListener> listener);
    virtual void detach(std::shared_ptr<HierarchicModelListener> listener);

private:
    std::shared_ptr<CNHierarchy> hierarchy;
    std::vector< std::weak_ptr<HierarchicModelListener> > listeners;
};

#endif //CROSSVIEWS_HIERARCHICMODEL_H
