#ifndef CROSSNATIVE_HIERARCHY_H
#define CROSSNATIVE_HIERARCHY_H

#include <memory>
#include <vector>

#include "CNHierarchyIndex.h"
#include "CNIndexOutOfBoundsException.h"

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
    virtual void add(std::shared_ptr<CNHierarchyNode> node, CNHierarchyIndex parentIndex);
    virtual void remove(std::shared_ptr<CNHierarchyNode> node, CNHierarchyIndex parentIndex);

    virtual void insert(std::shared_ptr<CNHierarchyNode> node, CNHierarchyIndex parentIndex, int childPos);
    virtual void remove(CNHierarchyIndex parentIndex, int childPos);

    virtual std::shared_ptr<CNHierarchyNode> retrieve(CNHierarchyIndex index);

private:
    std::shared_ptr<CNHierarchyNode> root;
    std::vector< std::shared_ptr<CNHierarchyNode> > nodes;
};

#endif //CROSSNATIVE_HIERARCHY_H
