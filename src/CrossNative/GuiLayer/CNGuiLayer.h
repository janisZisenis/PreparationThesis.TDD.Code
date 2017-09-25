#ifndef CROSSNATIVE_GUILAYER_H
#define CROSSNATIVE_GUILAYER_H

#include <memory>
#include <CrossNative/CrossNative_EXPORT.h>

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
//    virtual std::shared_ptr<CNView> findMatching(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> root);
//    virtual std::shared_ptr<CNView> findMatchingInChildren(std::shared_ptr<CNMatcher> matcher,
//                                                           std::shared_ptr<CNView> parent);
//    virtual bool isMatching(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> view);
private:
    std::shared_ptr<CNView> topLevelView;
};


#endif //CROSSNATIVE_GUILAYER_H