#ifndef CROSSNATIVE_COMPONENTLOADER_H
#define CROSSNATIVE_COMPONENTLOADER_H

#include <memory>

class CNComponent;
class CNMatcher;

class CNComponentLoader;
typedef std::shared_ptr<CNComponentLoader> CNComponentLoaderPtr;

class CNComponentLoader {
public:
    virtual ~CNComponentLoader() {}
protected:
    CNComponentLoader() {}

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) = 0;
};

#endif //CROSSNATIVE_COMPONENTLOADER_H