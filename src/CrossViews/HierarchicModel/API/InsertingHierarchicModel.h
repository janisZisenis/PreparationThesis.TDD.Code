#ifndef LVICE_INSERTINGHIERARCHICMODEL_H
#define LVICE_INSERTINGHIERARCHICMODEL_H

#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;

class InsertingHierarchicModel;
typedef std::shared_ptr<InsertingHierarchicModel> InsertingHierarchicModelPtr;

class InsertingHierarchicModel {
public:
    virtual ~InsertingHierarchicModel() {};
protected:
    InsertingHierarchicModel() {};

public:
    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex&, int childPos) = 0;
    virtual void remove(const CNHierarchyIndex& parent, int childPos) = 0;

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) = 0;
};

#endif //LVICE_INSERTINGHIERARCHICMODEL_H
