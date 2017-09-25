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
    CNViewPtr parent = findParent(matcher, topLevelView);

    if(parent)
        parent->add(view);
}

CNViewPtr CNGuiLayer::findParent(CNMatcherPtr matcher, CNViewPtr root) {
    if(matcher->matches(root)) {
        return root;
    }

    CNViewPtr parent;
    for (int i = 0; i < root->getChildCount(); i++) {
        parent = findParent(matcher, root->getChild(i));
        if (parent) break;
    }
    return parent;
}
