#include "CNGuiLayer.h"

#include "CNView.h"
#include "CNMatcher.h"

#include <stack>

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
    std::stack<CNViewPtr> views;

    for (int i = 0; i < parent->getChildCount(); i++) {
        views.push(parent->getChild(i));
    }

    while(!views.empty()) {
        if(isMatching(matcher, views.top()))
            return views.top();
        else {
            CNViewPtr top = views.top();
            views.pop();
            for(int i = 0; i < top->getChildCount(); i++) {
                views.push(top->getChild(i));
            }
        }
    }

//    for (int i = 0; i < parent->getChildCount(); i++) {
//        CNViewPtr matchingView = findMatchingViewInHierarchy(matcher, parent->getChild(i));
//
//        if (matchingView)
//            return matchingView;
//    }

    return nullptr;
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}

//class PreOrderIterator;
//typedef std::shared_ptr<PreOrderIterator> PreOrderIteratorPtr;
//class PreOrderIterator : public CNIterator {
//public:
//    static PreOrderIteratorPtr getNewInstance() {
//        return PreOrderIteratorPtr(new PreOrderIterator());
//    }
//    virtual ~PreOrderIterator() {}
//private:
//    PreOrderIterator() {}
//
//public:
//    virtual void first() override {}
//    virtual void next() override {}
//    virtual bool isDone() override {
//        return false;
//    }
//    virtual CNViewPtr current() override {
//        return nullptr;
//    }
//};