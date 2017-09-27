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
    views = std::stack<CNViewPtr>();
    localRoot = parent;

    first();

    while(!isDone()) {
        if(isMatching(matcher, current()))
            return current();
        else {
            next();
        }
    }

    return nullptr;
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}

void CNGuiLayer::first() {
    for (int i = 0; i < localRoot->getChildCount(); i++) {
        views.push(localRoot->getChild(i));
    }
}

void CNGuiLayer::next() {
    CNViewPtr top = views.top();
    views.pop();
    for(int i = 0; i < top->getChildCount(); i++) {
    views.push(top->getChild(i));
}
}

CNViewPtr CNGuiLayer::current() {
    return views.top();
}

bool CNGuiLayer::isDone() {
    return views.empty();
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