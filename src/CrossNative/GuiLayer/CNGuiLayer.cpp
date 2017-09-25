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

void CNGuiLayer::load(CNViewPtr view, CNMatcherPtr matcher) {
    if(matcher->matches(topLevelView))
        topLevelView->add(view);
    else
        for(int i = 0; i < topLevelView->getChildCount(); i++)
            if (matcher->matches(topLevelView->getChild(i))) {
                topLevelView->getChild(i)->add(view);
                break;
            }
}
