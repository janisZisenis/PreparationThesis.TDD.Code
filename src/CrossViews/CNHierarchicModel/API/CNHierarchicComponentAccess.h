#ifndef CROSSNATIVE_HIERARCHICCOMPONENTACCESS_H
#define CROSSNATIVE_HIERARCHICCOMPONENTACCESS_H

#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;
class CNHierarchicModelListener;

class CNHierarchicComponentAccess;
typedef std::shared_ptr<CNHierarchicComponentAccess> CNHierarchicComponentAccessPtr;

class CNHierarchicComponentAccess {
public:
    virtual ~CNHierarchicComponentAccess() {};
protected:
    CNHierarchicComponentAccess() {};

public:
    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) = 0;

    virtual void addListener(std::shared_ptr<CNHierarchicModelListener> listener) = 0;
    virtual void removeListener(std::shared_ptr<CNHierarchicModelListener> listener) = 0;
};

#endif //CROSSNATIVE_HIERARCHICCOMPONENTACCESS_H
