#ifndef CROSSNATIVE_HIERARCHICMODEL_H
#define CROSSNATIVE_HIERARCHICMODEL_H

#include "CrossViews/Commands/CNAddCommand/CNComponentAdder.h"
#include "CrossViews/Commands/CNRemoveCommand/CNComponentInserter.h"
#include "CrossViews/CNHierarchicModel/API/CNHierarchicComponentAccess.h"

class CNVisitable;
class CNComponent;
class CNHierarchy;

class CNHierarchicModelListener;

class CNHierarchicModel;
typedef std::shared_ptr<CNHierarchicModel> CNHierarchicModelPtr;

class CNHierarchicModel : public CNComponentAdder, public CNComponentInserter, public CNHierarchicComponentAccess {
public:
    static CNHierarchicModelPtr getNewInstance();
    virtual ~CNHierarchicModel();
protected:
    CNHierarchicModel();

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override;
    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) override;

    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent, int childPos) override;
    virtual void remove(const CNHierarchyIndex& parent, int childPos) override;

    virtual void notifyInserted(std::shared_ptr<CNVisitable> visitable, const CNHierarchyIndex& parent, int childPos);
    virtual void notifyRemoved(const CNHierarchyIndex& parent);

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& parent) override;

    virtual void addListener(std::shared_ptr<CNHierarchicModelListener> listener) override;
    virtual void removeListener(std::shared_ptr<CNHierarchicModelListener> listener) override;

private:
    std::shared_ptr<CNHierarchy> hierarchy;
    std::vector< std::weak_ptr<CNHierarchicModelListener> > listeners;
};

#endif //CROSSNATIVE_HIERARCHICMODEL_H
