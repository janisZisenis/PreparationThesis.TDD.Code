#include "CNGuiLayer.h"

#include "CNView.h"
#include "CNMatcher.h"

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

void CNGuiLayer::load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> matcher) {
    if(matcher->matches(topLevelView))
        topLevelView->add(view);
    else
        if(topLevelView->getChildCount() == 1)
            if(matcher->matches(topLevelView->getChild(0)))
                topLevelView->getChild(0)->add(view);

}
