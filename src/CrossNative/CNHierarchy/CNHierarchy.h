#ifndef CROSSNATIVE_HIERARCHY_H
#define CROSSNATIVE_HIERARCHY_H

#include <memory>
#include <vector>

#include "CNHierarchyIndex.h"
#include "CNIndexNotExistingException.h"
#include "CNInvalidIndexException.h"

class CNComponent;

class CNHierarchy;
typedef std::shared_ptr<CNHierarchy> CNHierarchyPtr;

class CNHierarchy {
public:
    static CNHierarchyPtr getNewInstance();
    virtual ~CNHierarchy();
protected:
    CNHierarchy();

public:
    virtual void add(std::shared_ptr<CNComponent> node, CNHierarchyIndex parent);
    virtual void remove(std::shared_ptr<CNComponent> node, CNHierarchyIndex parent);

    virtual void insert(std::shared_ptr<CNComponent> node, CNHierarchyIndex parent, int childPos);
    virtual void remove(CNHierarchyIndex parent, int childPos);

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index);

private:
    virtual std::shared_ptr<CNComponent> find(const CNHierarchyIndex& index);
private:
    std::shared_ptr<CNComponent> root;
    std::vector< std::shared_ptr<CNComponent> > nodes;
};

#endif //CROSSNATIVE_HIERARCHY_H
