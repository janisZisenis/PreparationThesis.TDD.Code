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

private:
    std::vector< std::shared_ptr<CNView> > views;
};

#endif //CROSSNATIVE_GUILAYER_H