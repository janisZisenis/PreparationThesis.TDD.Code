#ifndef CROSSVIEWS_COMPONENTLOADER_H
#define CROSSVIEWS_COMPONENTLOADER_H

#include <memory>

class CNComponent;
class CNMatcher;

class ComponentLoader;
typedef std::shared_ptr<ComponentLoader> ComponentLoaderPtr;

class ComponentLoader {
public:
    virtual ~ComponentLoader() {}
protected:
    ComponentLoader() {}

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) = 0;
};

#endif //CROSSVIEWS_COMPONENTLOADER_H