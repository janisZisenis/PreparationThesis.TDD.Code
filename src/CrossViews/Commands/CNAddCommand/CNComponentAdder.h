#ifndef CROSSNATIVE_COMPONENTADDER_H
#define CROSSNATIVE_COMPONENTADDER_H

#include <memory>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;

class CNComponentAdder;
typedef std::shared_ptr<CNComponentAdder> CNComponentAdderPtr;

class CNComponentAdder {
public:
    virtual ~CNComponentAdder() {};
protected:
    CNComponentAdder() {};

public:
    virtual void add(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) = 0;
    virtual void remove(std::shared_ptr<CNComponent> component, const CNHierarchyIndex& parent) = 0;

    virtual std::shared_ptr<CNComponent> retrieve(const CNHierarchyIndex& index) = 0;
};

#endif //CROSSNATIVE_COMPONENTADDER_H
