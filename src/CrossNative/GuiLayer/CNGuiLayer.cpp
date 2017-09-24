#include "CNGuiLayer.h"

#include "CNView.h"

CNGuiLayerPtr CNGuiLayer::getNewInstance() {
    return CNGuiLayerPtr(new CNGuiLayer());
}

CNGuiLayer::~CNGuiLayer() {

}

CNGuiLayer::CNGuiLayer() {

}

void CNGuiLayer::loadTopLevel(std::shared_ptr<CNView> view) {
    topLevelView = view;
}

void CNGuiLayer::load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> machter) {
    topLevelView->add(view);
}
