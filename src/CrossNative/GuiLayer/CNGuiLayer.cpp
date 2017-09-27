#include "CNGuiLayer.h"

#include "CNView.h"
#include "CNMatcher.h"

CNGuiLayer::PreOrderIteratorPtr CNGuiLayer::PreOrderIterator::getNewInstance(CNViewPtr root) {
    return PreOrderIteratorPtr(new PreOrderIterator(root));
}

CNGuiLayer::PreOrderIterator::~PreOrderIterator() {}

CNGuiLayer::PreOrderIterator::PreOrderIterator(CNViewPtr root) : root(root) {}

void CNGuiLayer::PreOrderIterator::first() {
    pushChildrenOf(root);
}

void CNGuiLayer::PreOrderIterator::next() {
    CNViewPtr currentView = current();
    moveCurrent();
    pushChildrenOf(currentView);
}

bool CNGuiLayer::PreOrderIterator::isDone() {
    return iterators.empty();
}

CNViewPtr CNGuiLayer::PreOrderIterator::current() {
    return iterators.top()->current();
}

void CNGuiLayer::PreOrderIterator::pushChildrenOf(CNViewPtr parent) {
    CNIteratorPtr it = parent->makeIterator();
    it->first();
    if(!it->isDone())
        iterators.push(it);
}

void CNGuiLayer::PreOrderIterator::moveCurrent() {
    iterators.top()->next();
    if(iterators.top()->isDone())
        iterators.pop();
}



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
    PreOrderIteratorPtr it = makeHierarchyIterator(parent);

    for(it->first(); !it->isDone(); it->next()) {
        if(isMatching(matcher, it->current()))
            return it->current();
    }

    return nullptr;
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}

CNGuiLayer::PreOrderIteratorPtr CNGuiLayer::makeHierarchyIterator(CNViewPtr root) {
    return PreOrderIterator::getNewInstance(root);
}
