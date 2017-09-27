#ifndef CROSSNATIVE_GUILAYER_H
#define CROSSNATIVE_GUILAYER_H

#include <memory>
#include <vector>
#include <CrossNative/CrossNative_EXPORT.h>
#include <stack>

class CNView;
class CNMatcher;

class CNGuiLayer;
typedef std::shared_ptr<CNGuiLayer> CNGuiLayerPtr;

class CrossNative_EXPORT CNGuiLayer {
public:
    static CNGuiLayerPtr getNewInstance();
    virtual ~CNGuiLayer();

protected:
    CNGuiLayer();

public:
    virtual void loadTopLevel(std::shared_ptr<CNView> view);
    virtual void load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> machter);

private:
    virtual std::shared_ptr<CNView> findMatchingViewInHierarchy(std::shared_ptr<CNMatcher> matcher,
                                                                std::shared_ptr<CNView> root);
    virtual std::shared_ptr<CNView> findMatchingView(std::shared_ptr<CNMatcher> matcher);
    virtual std::shared_ptr<CNView> findMatchingInChildren(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> parent);
    virtual bool isMatching(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> view);

    virtual void first();
    virtual void next();
    virtual std::shared_ptr<CNView> current();
    virtual bool isDone();
private:
    std::vector< std::shared_ptr<CNView> > viewHierarchies;

    std::stack< std::shared_ptr<CNView> > views;
    std::shared_ptr<CNView> localRoot;
};


#endif //CROSSNATIVE_GUILAYER_H