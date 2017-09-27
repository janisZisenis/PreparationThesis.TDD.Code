#include "CNGuiLayer.h"

#include "CNView.h"
#include "CNMatcher.h"

class PreOrderIterator;
typedef std::shared_ptr<PreOrderIterator> PreOrderIteratorPtr;
class PreOrderIterator {
public:
    static PreOrderIteratorPtr getNewInstance(CNViewPtr root) {
        return PreOrderIteratorPtr(new PreOrderIterator(root));
    }
    virtual ~PreOrderIterator() {}
private:
    PreOrderIterator(CNViewPtr root) : root(root) {}

public:
    virtual void first() {
        pushChildrenOf(root);
    }
    virtual void next() {
        CNViewPtr currentView = current();
        moveOverCurrent();
        pushChildrenOf(currentView);
    }
    virtual bool isDone() {
        return iterators.empty();
    }
    virtual CNViewPtr current() {
        return iterators.top()->current();
    }
private:
    virtual void pushChildrenOf(CNViewPtr parent) {
        CNIteratorPtr it = parent->makeIterator();
        it->first();
        if(!it->isDone())
            iterators.push(it);
    }
    virtual void moveOverCurrent() {
        iterators.top()->next();
        if(iterators.top()->isDone())
            iterators.pop();
    }

private:
    std::stack<CNIteratorPtr> iterators;
    CNViewPtr root;
};

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
    PreOrderIteratorPtr it = PreOrderIterator::getNewInstance(parent);

    for(it->first(); !it->isDone(); it->next()) {
        if(isMatching(matcher, it->current()))
            return it->current();
    }

    return nullptr;
}

bool CNGuiLayer::isMatching(CNMatcherPtr matcher, CNViewPtr view) {
    return matcher->matches(view);
}
