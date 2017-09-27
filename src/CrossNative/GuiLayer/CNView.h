#ifndef CROSSNATIVE_VIEW_H
#define CROSSNATIVE_VIEW_H

#include <memory>

#include "CNIterator.h"

class CNView;
typedef std::shared_ptr<CNView> CNViewPtr;

class CNView {
public:
    virtual ~CNView() {};
protected:
    CNView() {};

public:
    virtual void add(CNViewPtr view) = 0;
    virtual CNIteratorPtr makeIterator() = 0;
    virtual CNViewPtr getChild(int position) = 0;
    virtual int getChildCount() = 0;
};


#endif //CROSSNATIVE_VIEW_H