#include "CNGuiLayer.h"
#include <Hierarchies/CNDynamicHierarchy/CNDynamicHierarchy.h>

CNGuiLayerPtr CNGuiLayer::getNewInstance() {
    return CNGuiLayerPtr(new CNGuiLayer());
}
CNGuiLayer::~CNGuiLayer() {}
CNGuiLayer::CNGuiLayer() : hierarchy(CNDynamicHierarchy::getNewInstance()) {}

void CNGuiLayer::load(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) {
    hierarchy->load(component, matcher);
}

void CNGuiLayer::unload(std::shared_ptr<CNComponent> component) {
    hierarchy->unload(component);
}

void CNGuiLayer::move(std::shared_ptr<CNComponent> component, std::shared_ptr<CNMatcher> matcher) {
    hierarchy->move(component, matcher);
}
