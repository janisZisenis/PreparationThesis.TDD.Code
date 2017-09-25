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

void CNGuiLayer::loadTopLevel(CNViewPtr view) {
    topLevelView = view;
}

void CNGuiLayer::load(CNViewPtr view, CNMatcherPtr matcher) {
    CNViewPtr matching = findMatching(matcher, topLevelView);

    if(matching)
        matching->add(view);
}

CNViewPtr CNGuiLayer::findMatching(CNMatcherPtr matcher, CNViewPtr root) {
    return isMatching(matcher, root) ? root : findMatchingChild(matcher, root);
}

CNViewPtr CNGuiLayer::findMatchingChild(CNMatcherPtr matcher, CNViewPtr parent) {
    return parent->getChildCount() == 0 ? nullptr : findMatching(matcher, parent->getChild(0));
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}
