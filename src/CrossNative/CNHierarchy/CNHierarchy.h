#ifndef CROSSNATIVE_HIERARCHY_H
#define CROSSNATIVE_HIERARCHY_H

#include <memory>

#include "CNHierarchyIndex.h"

class CNHierarchyNode;

class CNHierarchy;
typedef std::shared_ptr<CNHierarchy> CNHierarchyPtr;

class CNHierarchy {
public:
    static CNHierarchyPtr getNewInstance();
    virtual ~CNHierarchy();
protected:
    CNHierarchy();

public:
    virtual void add(std::shared_ptr<CNHierarchyNode> component, CNHierarchyIndex parentIndex);
    virtual void remove(std::shared_ptr<CNHierarchyNode> component, CNHierarchyIndex parentIndex);

    virtual void insert(std::shared_ptr<CNHierarchyNode> component, CNHierarchyIndex parentIndex, int childPos);
    virtual void remove(CNHierarchyIndex parentIndex, int childPos);

    virtual int getChildCountFor(CNHierarchyIndex index);
    virtual std::shared_ptr<CNHierarchyNode> retrieve(CNHierarchyIndex index);
private:
    virtual std::shared_ptr<CNHierarchyNode> findComponent(CNHierarchyIndex index);
};

#endif //CROSSNATIVE_HIERARCHY_H
