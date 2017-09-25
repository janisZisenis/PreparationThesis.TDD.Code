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

CNViewPtr CNGuiLayer::findMatching(CNMatcherPtr matcher, CNViewPtr parent) {
    return isMatching(matcher, parent) ? parent : findMatchingInChildren(matcher, parent);
}

CNViewPtr CNGuiLayer::findMatchingInChildren(CNMatcherPtr matcher, CNViewPtr parent) {
    CNViewPtr matching = nullptr;

    for(int i = 0; i < parent->getChildCount(); i++)
        matching = findMatching(matcher, parent->getChild(i));

    return matching;
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}
