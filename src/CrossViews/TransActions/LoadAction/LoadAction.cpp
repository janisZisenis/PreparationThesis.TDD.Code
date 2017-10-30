#include "LoadAction.h"
#include "ComponentLoader.h"
#include "CreateComponentStrategy.h"
#include "CrossHierarchies/CNMatcher/CNMatcher.h"

LoadActionPtr LoadAction::getNewInstance(ComponentLoaderPtr componentLoader,
                                             CreateComponentStrategyPtr componentStrategy,
                                             CNMatcherPtr matcher) {
    return LoadActionPtr(new LoadAction(componentLoader, componentStrategy, matcher));
}
LoadAction::~LoadAction() {}
LoadAction::LoadAction(ComponentLoaderPtr componentLoader,
                           CreateComponentStrategyPtr componentStrategy,
                           CNMatcherPtr matcher)
        : componentLoader(componentLoader),
          componentStrategy(componentStrategy),
          matcher(matcher){}

void LoadAction::execute() {
    try {
        std::shared_ptr<CNComponent> component = componentStrategy->createComponent();
        componentLoader->load(component, matcher);
    } catch (CreationCanceledException& e) {}
}
