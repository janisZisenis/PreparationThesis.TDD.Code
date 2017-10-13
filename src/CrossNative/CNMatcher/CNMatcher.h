#ifndef CROSSNATIVE_MATCHER_H
#define CROSSNATIVE_MATCHER_H

#include <memory>

class CNComponent;

class CNMatcher;
typedef std::shared_ptr<CNMatcher> CNMatcherPtr;

class CNMatcher {
public:
    virtual ~CNMatcher() {};
protected:
    CNMatcher() {};

public:
    virtual bool matches(std::shared_ptr<CNComponent> view) = 0;
};


#endif //CROSSNATIVE_MATCHER_H