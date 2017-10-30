#ifndef CROSSVIEWS_GUILAYER_H
#define CROSSVIEWS_GUILAYER_H

#include "CrossViews/TransActions/LoadAction/ComponentLoader.h"

class CNDynamicHierarchy;
class CNComponent;
class CNMatcher;

class CNGuiLayer;
typedef std::shared_ptr<CNGuiLayer> GuiLayerPtr;

class CNGuiLayer : public ComponentLoader {
public:
    static GuiLayerPtr getNewInstance();
    virtual ~CNGuiLayer();
private:
    CNGuiLayer();

public:
    void load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) override;
    void unload(std::shared_ptr<CNComponent> component);
    void move(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher);

private:
    std::shared_ptr<CNDynamicHierarchy> hierarchy;
};

#endif //CROSSVIEWS_GUILAYER_H
