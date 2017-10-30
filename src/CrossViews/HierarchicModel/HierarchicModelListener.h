#ifndef CROSSVIEWS_HIERARCHICMODELLISTENER_H
#define CROSSVIEWS_HIERARCHICMODELLISTENER_H

#include <memory>
#include "CrossHierarchies/CNHierarchy/CNHierarchyIndex.h"

class CNVisitable;

class HierarchicModelListener;
typedef std::shared_ptr<HierarchicModelListener> HierarchicModelListenerPtr;

class HierarchicModelListener {
public:
    virtual ~HierarchicModelListener() {};
protected:
    HierarchicModelListener() {};

public:
    virtual void onRemove(const CNHierarchyIndex& index) = 0;
    virtual void onInsert(std::shared_ptr<CNVisitable> visitable, const CNHierarchyIndex& parent, int childPos) = 0;
};

#endif //CROSSVIEWS_HIERARCHICMODELLISTENER_H
