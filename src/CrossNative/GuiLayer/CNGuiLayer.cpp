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
    CNViewPtr parent;

    if(matcher->matches(topLevelView))
        parent = topLevelView;
    else
        for(int i = 0; i < topLevelView->getChildCount(); i++)
            if (matcher->matches(topLevelView->getChild(i))) {
                parent = topLevelView->getChild(i);
                break;
            }

    if(parent)
        parent->add(view);
}
