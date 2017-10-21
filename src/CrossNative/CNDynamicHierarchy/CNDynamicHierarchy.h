#ifndef CROSSNATIVE_CNDYNAMICHIERARCHY_H
#define CROSSNATIVE_CNDYNAMICHIERARCHY_H

#include <memory>
#include <vector>
#include <string>
#include <CrossNative/CrossNative_EXPORT.h>

class CNHierarchyNodeAlreadyLoadedException : public std::exception {
    const char *what() const throw() override {
        return std::string("The component was already loaded, components can't be loaded more than once!").c_str();
    }
};

class CNHierarchyNodeNotLoadedException : public std::exception {
    const char *what() const throw() override {
        return std::string("The given component was not loaded before unloading!").c_str();
    }
};

class CNComponent;
class CNMatcher;

class CNDynamicHierarchy;
typedef std::shared_ptr<CNDynamicHierarchy> CNDynamicHierarchyPtr;

class CrossNative_EXPORT CNDynamicHierarchy {
public:
    static CNDynamicHierarchyPtr getNewInstance();
    virtual ~CNDynamicHierarchy();

protected:
    CNDynamicHierarchy();

public:
    virtual void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher);
    virtual void unload(std::shared_ptr<CNComponent> component);
    virtual void move(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher);

private:
    virtual void loadComponent(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher);
    virtual void unloadComponent(std::shared_ptr<CNComponent> component);

    virtual void addToComponentList(std::shared_ptr<CNComponent> component);
    virtual void addToParent(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher);
    virtual void removeFromComponentList(std::shared_ptr<CNComponent> component);
    virtual void removeFromParent(std::shared_ptr<CNComponent> component);

    virtual bool isAlreadyLoaded(std::shared_ptr<CNComponent> component);
    virtual int findPosition(std::shared_ptr<CNComponent> component);
private:
    std::vector< std::shared_ptr<CNComponent> > components;
};

#endif //CROSSNATIVE_CNDYNAMICHIERARCHY_H