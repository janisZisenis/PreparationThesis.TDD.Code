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
    else {
        if (topLevelView->getChildCount() == 1)
            if(matcher->matches(topLevelView->getChild(0)))
                topLevelView->getChild(0)->add(view);
    }
}

//void CNGuiLayer::load(CNViewPtr view, CNMatcherPtr matcher) {
//    CNViewPtr parent = findMatching(matcher, topLevelView);
//
//    if(parent)
//        parent->add(view);
//}

//CNViewPtr CNGuiLayer::findMatching(CNMatcherPtr matcher, CNViewPtr root) {
//    return isMatching(matcher, root) ? root : findMatchingInChildren(matcher, root);
//}
//
//CNViewPtr CNGuiLayer::findMatchingInChildren(CNMatcherPtr matcher, CNViewPtr parent) {
//    CNViewPtr matching = nullptr;
//
//    for (int i = 0; i < parent->getChildCount(); i++) {
//        matching = findMatching(matcher, parent->getChild(i));
//        if(matching) break;
//    }
//
//    return matching;
//}
//
//bool CNGuiLayer::isMatching(std::shared_ptr<CNMatcher> matcher, std::shared_ptr<CNView> view) {
//    return matcher->matches(view);
//}
