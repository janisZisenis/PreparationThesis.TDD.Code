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
    viewHierarchies.push_back(view);
}

void CNGuiLayer::load(CNViewPtr view, CNMatcherPtr matcher) {
    CNViewPtr matchingView = findMatchingView(matcher);

    if(matchingView)
        matchingView->add(view);
}

CNViewPtr CNGuiLayer::findMatchingView(CNMatcherPtr matcher) {
    for(int i = 0; i < viewHierarchies.size(); i++) {
        CNViewPtr matchingView = findMatchingViewInHierarchy(matcher, viewHierarchies[i]);

        if (matchingView)
            return matchingView;
    }

    return nullptr;
}

CNViewPtr CNGuiLayer::findMatchingViewInHierarchy(CNMatcherPtr matcher, CNViewPtr root) {
    return isMatching(matcher, root) ? root : findMatchingInChildren(matcher, root);
}

CNViewPtr CNGuiLayer::findMatchingInChildren(CNMatcherPtr matcher, CNViewPtr parent) {
    CNIteratorPtr it = parent->makeIterator();
    for (it->first(); !it->isDone(); it->next()) {
        CNViewPtr matchingView = findMatchingViewInHierarchy(matcher, it->current());

        if (matchingView)
            return matchingView;
    }

    return nullptr;
}


bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}