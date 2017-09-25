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
    topLevelViews.push_back(view);
}

void CNGuiLayer::load(CNViewPtr view, CNMatcherPtr matcher) {
    CNViewPtr matching = findMatching(matcher);

    if(matching)
        matching->add(view);
}

CNViewPtr CNGuiLayer::findMatching(CNMatcherPtr matcher) {
    CNViewPtr matching = nullptr;

    for(int i = 0; i < topLevelViews.size(); i++) {
        matching = findMatchingInViewHierarchy(matcher, topLevelViews[i]);

        if (matching)
            break;
    }

    return matching;
}

CNViewPtr CNGuiLayer::findMatchingInViewHierarchy(CNMatcherPtr matcher, CNViewPtr root) {
    return isMatching(matcher, root) ? root : findMatchingInChildren(matcher, root);
}

CNViewPtr CNGuiLayer::findMatchingInChildren(CNMatcherPtr matcher, CNViewPtr parent) {
    CNViewPtr matching = nullptr;

    for(int i = 0; i < parent->getChildCount(); i++)
        matching = findMatchingInViewHierarchy(matcher, parent->getChild(i));

    return matching;
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}