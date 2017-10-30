#ifndef CROSSNATIVE_COMPONENT_H
#define CROSSNATIVE_COMPONENT_H

#include <memory>
#include "CrossHierarchies/CNVisitable/CNVisitable.h"
#include "CNChildNotFoundException.h"
#include "CNInvalidInsertingPositionException.h"
#include "CNInvalidChildPositionException.h"

class CNComponent;
typedef std::shared_ptr<CNComponent> CNComponentPtr;
class CNComponent : public virtual CNVisitable {
public:
    virtual  ~CNComponent() {};

protected:
    CNComponent() {};

public:
    virtual bool isParentOf(CNComponentPtr component) = 0;
    virtual int getChildCount() = 0;
    virtual CNComponentPtr getChild(int childPosition) = 0;

    virtual void add(CNComponentPtr component) = 0;
    virtual void remove(CNComponentPtr component) = 0;
    virtual void insert(CNComponentPtr component, int childPos) = 0;
    virtual void remove(int childPos) = 0;
};

#endif //CROSSNATIVE_COMPONENT_H