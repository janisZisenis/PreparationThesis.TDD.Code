#ifndef CROSSNATIVE_GUILAYER_H
#define CROSSNATIVE_GUILAYER_H

#include <memory>
#include <vector>
#include <CrossNative/CrossNative_EXPORT.h>
#include <stack>

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
    std::shared_ptr<CNView> firstView;
    std::shared_ptr<CNView> secondView;
};

#endif //CROSSNATIVE_GUILAYER_H