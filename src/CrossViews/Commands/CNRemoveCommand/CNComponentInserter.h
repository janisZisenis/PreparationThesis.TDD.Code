#ifndef CROSSNATIVE_COMPONENTINSERTER_H
#define CROSSNATIVE_COMPONENTINSERTER_H

#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;

class CNComponentInserter;
typedef std::shared_ptr<CNComponentInserter> CNComponentInserterPtr;

class CNComponentInserter {
public:
    virtual ~CNComponentInserter() {};
protected:
    CNComponentInserter() {};

public:
    virtual void insert(std::shared_ptr<CNComponent> component, const CNHierarchyIndex&, int childPos) = 0;
    virtual void remove(const CNHierarchyIndex& parent, int childPos) = 0;

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) = 0;
};

#endif //CROSSNATIVE_COMPONENTINSERTER_H
