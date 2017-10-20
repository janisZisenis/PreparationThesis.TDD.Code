#ifndef CROSSVIEWS_HIERARCHICMODELACCESS_H
#define CROSSVIEWS_HIERARCHICMODELACCESS_H

#include <memory>
#include "CrossViews/HierarchyIndex/HierarchyIndex.h"

class CNVisitable;

class HierarchicModelAccess;
typedef std::shared_ptr<HierarchicModelAccess> HierarchicModelAccessPtr;

class HierarchicModelAccess {
public:
    virtual ~HierarchicModelAccess() {};
protected:
    HierarchicModelAccess() {};

public:
    virtual std::shared_ptr<CNVisitable> retrieve(const HierarchyIndex& index) = 0;
};

#endif //CROSSVIEWS_HIERARCHICMODELACCESS_H
