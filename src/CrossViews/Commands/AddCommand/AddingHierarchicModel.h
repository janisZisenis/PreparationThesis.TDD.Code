#ifndef CROSSVIEWS_ADDINGHIERARCHICMODEL_H
#define CROSSVIEWS_ADDINGHIERARCHICMODEL_H

#include <memory>
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;

class AddingHierarchicModel;
typedef std::shared_ptr<AddingHierarchicModel> AddingHierarchicModelPtr;

class AddingHierarchicModel {
public:
    virtual ~AddingHierarchicModel() {};
protected:
    AddingHierarchicModel() {};

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) = 0;
    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) = 0;

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) = 0;
};

#endif //CROSSVIEWS_ADDINGHIERARCHICMODEL_H
