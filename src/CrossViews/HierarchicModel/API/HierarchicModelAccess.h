#ifndef CROSSVIEWS_HIERARCHICMODELACCESS_H
#define CROSSVIEWS_HIERARCHICMODELACCESS_H

#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;

class HierarchicModelAccess;
typedef std::shared_ptr<HierarchicModelAccess> HierarchicModelAccessPtr;

class HierarchicModelAccess {
public:
    virtual ~HierarchicModelAccess() {};
protected:
    HierarchicModelAccess() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) = 0;
};

#endif //CROSSVIEWS_HIERARCHICMODELACCESS_H
