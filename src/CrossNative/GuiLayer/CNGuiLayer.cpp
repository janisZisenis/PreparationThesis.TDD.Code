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
        for (int i = 0; i < root->getChildCount(); i++) {
            views.push(root->getChild(i));
        }
    }
    virtual void next() {
        CNViewPtr top = views.top();
        views.pop();
        for(int i = 0; i < top->getChildCount(); i++) {
            views.push(top->getChild(i));
        }
    }
    virtual bool isDone() {
        return views.empty();
    }
    virtual CNViewPtr current() {
        return views.top();
    }

private:
    std::stack< std::shared_ptr<CNView> > views;
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
