#ifndef CROSSNATIVE_GUILAYER_H
#define CROSSNATIVE_GUILAYER_H

#include <memory>
#include <vector>
#include <string>
#include <CrossNative/CrossNative_EXPORT.h>

class CNViewAlreadyLoadedException : public std::exception {
    const char *what() const throw() override {
        return std::string("The view was already loaded, views can't be loaded more than once!").c_str();
    }
};

class CNViewNotLoadedException : public std::exception {
    const char *what() const throw() override {
        return std::string("The given view was not loaded before unloading!").c_str();
    }
};

class CNView;
class CNMatcher;

class CNDynamicViewHierarchy;
typedef std::shared_ptr<CNDynamicViewHierarchy> CNDynamicViewHierarchyPtr;

class CrossNative_EXPORT CNDynamicViewHierarchy {
public:
    static CNDynamicViewHierarchyPtr getNewInstance();
    virtual ~CNDynamicViewHierarchy();

protected:
    CNDynamicViewHierarchy();

public:
    virtual void load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> matcher);
    virtual void unload(std::shared_ptr<CNView> view);

private:
    virtual void loadView(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> matcher);
    virtual void unloadView(std::shared_ptr<CNView> view);

    virtual void addToViewList(std::shared_ptr<CNView> view);
    virtual void addToParent(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> matcher);
    virtual void removeFromViewList(std::shared_ptr<CNView> view);
    virtual void removeFromParent(std::shared_ptr<CNView> view);

    virtual bool isAlreadyLoaded(std::shared_ptr<CNView> view);
    virtual int findPosition(std::shared_ptr<CNView> view);
private:
    std::vector< std::shared_ptr<CNView> > views;
};

#endif //CROSSNATIVE_GUILAYER_H