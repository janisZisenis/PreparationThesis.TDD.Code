#ifndef CROSSNATIVE_COMPONENT_H
#define CROSSNATIVE_COMPONENT_H

#include <string>
#include "CrossNative/CNVisitable/CNVisitable.h"
#include "CNChildNotFoundException.h"

class CNComponent;
typedef std::shared_ptr<CNComponent> CNComponentPtr;

class CNComponent : public CNVisitable {
public:
    virtual ~CNComponent() {};
protected:
    CNComponent() {};

public:
    virtual void add(CNComponentPtr view) = 0;
    virtual void remove(CNComponentPtr view) = 0;
    virtual bool isParentOf(CNComponentPtr view) = 0;
};

#endif //CROSSNATIVE_COMPONENT_H