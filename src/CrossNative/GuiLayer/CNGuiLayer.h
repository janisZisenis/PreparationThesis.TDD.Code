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
    virtual std::shared_ptr<CNView> findParent(std::shared_ptr<CNMatcher> matcher);

private:
    std::shared_ptr<CNView> topLevelView;
};


#endif //CROSSNATIVE_GUILAYER_H