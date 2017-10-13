#ifndef CROSSNATIVE_CNDYNAMICHIERARCHY_H
#define CROSSNATIVE_CNDYNAMICHIERARCHY_H

#include <memory>
#include <vector>
#include <string>
#include <CrossNative/CrossNative_EXPORT.h>

class CNComponentAlreadyLoadedException : public std::exception {
    const char *what() const throw() override {
        return std::string("The component was already loaded, views can't be loaded more than once!").c_str();
    }
};

class CNComponentNotLoadedException : public std::exception {
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
    virtual void load(std::shared_ptr<CNComponent> view, std::shared_ptr<CNMatcher> matcher);
    virtual void unload(std::shared_ptr<CNComponent> view);
    virtual void move(std::shared_ptr<CNComponent> view, std::shared_ptr<CNMatcher> matcher);

private:
    virtual void loadView(std::shared_ptr<CNComponent> view, std::shared_ptr<CNMatcher> matcher);
    virtual void unloadView(std::shared_ptr<CNComponent> view);

    virtual void addToViewList(std::shared_ptr<CNComponent> view);
    virtual void addToParent(std::shared_ptr<CNComponent> view, std::shared_ptr<CNMatcher> matcher);
    virtual void removeFromViewList(std::shared_ptr<CNComponent> view);
    virtual void removeFromParent(std::shared_ptr<CNComponent> view);

    virtual bool isAlreadyLoaded(std::shared_ptr<CNComponent> view);
    virtual int findPosition(std::shared_ptr<CNComponent> view);
private:
    std::vector< std::shared_ptr<CNComponent> > views;
};

#endif //CROSSNATIVE_CNDYNAMICHIERARCHY_H