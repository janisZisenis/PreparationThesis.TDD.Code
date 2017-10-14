#ifndef CROSSNATIVE_COMPONENT_H
#define CROSSNATIVE_COMPONENT_H

#include <string>
#include "CrossNative/CNVisitable/CNVisitable.h"

class CNChildNotFoundException : public std::exception {
    const char *what() const throw() override {
        return std::string("The removed component was not found in children!").c_str();
    }
};

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