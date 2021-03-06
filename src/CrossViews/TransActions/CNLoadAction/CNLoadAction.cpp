#include "CNLoadAction.h"
#include "CNComponentLoader.h"
#include "CNCreateComponentStrategy.h"
#include <Hierarchies/CNMatcher/CNMatcher.h>

CNLoadActionPtr CNLoadAction::getNewInstance(CNComponentLoaderPtr componentLoader,
                                             CNCreateComponentStrategyPtr componentStrategy,
                                             CNMatcherPtr matcher) {
    return CNLoadActionPtr(new CNLoadAction(componentLoader, componentStrategy, matcher));
}
CNLoadAction::~CNLoadAction() {}
CNLoadAction::CNLoadAction(CNComponentLoaderPtr componentLoader,
                           CNCreateComponentStrategyPtr componentStrategy,
                           CNMatcherPtr matcher)
        : componentLoader(componentLoader),
          componentStrategy(componentStrategy),
          matcher(matcher){}

void CNLoadAction::execute() {
    try {
        std::shared_ptr<CNComponent> component = componentStrategy->createComponent();
        componentLoader->load(component, matcher);
    } catch (CreationCanceledException& e) {}
}
