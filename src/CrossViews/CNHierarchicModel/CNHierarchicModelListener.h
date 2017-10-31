#ifndef CROSSNATIVE_HIERARCHICMODELLISTENER_H
#define CROSSNATIVE_HIERARCHICMODELLISTENER_H

#include <memory>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNVisitable;

class CNHierarchicModelListener;
typedef std::shared_ptr<CNHierarchicModelListener> CNHierarchicModelListenerPtr;

class CNHierarchicModelListener {
public:
    virtual ~CNHierarchicModelListener() {};
protected:
    CNHierarchicModelListener() {};

public:
    virtual void onRemove(const CNHierarchyIndex& index) = 0;
    virtual void onInsert(std::shared_ptr<CNVisitable> visitable, const CNHierarchyIndex& parent, int childPos) = 0;
};

#endif //CROSSNATIVE_HIERARCHICMODELLISTENER_H
