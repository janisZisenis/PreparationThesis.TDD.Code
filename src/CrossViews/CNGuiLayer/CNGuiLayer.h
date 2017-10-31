#ifndef CROSSNATIVE_GUILAYER_H
#define CROSSNATIVE_GUILAYER_H

#include "CrossViews/TransActions/CNLoadAction/CNComponentLoader.h"

class CNDynamicHierarchy;
class CNComponent;
class CNMatcher;

class CNGuiLayer;
typedef std::shared_ptr<CNGuiLayer> CNGuiLayerPtr;

class CNGuiLayer : public CNComponentLoader {
public:
    static CNGuiLayerPtr getNewInstance();
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

#endif //CROSSNATIVE_GUILAYER_H
