#ifndef CROSSNATIVE_VIEW_H
#define CROSSNATIVE_VIEW_H

#include <memory>

class CNView;
typedef std::shared_ptr<CNView> CNViewPtr;

class CNView {
public:
    virtual ~CNView() {};
protected:
    CNView() {};

public:
    virtual void add(CNViewPtr view) = 0;
    virtual void remove(CNViewPtr view) = 0;
    virtual bool isParentOf(CNViewPtr view) = 0;
};


#endif //CROSSNATIVE_VIEW_H