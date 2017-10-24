#include "AddAction.h"
#include "CreateComponentStrategy.h"
#include <CodeBase/CBCommandInvoker/CBCommandInvoker.h>
#include <CrossNative/CNComponent/CNComponent.h>
#include <CrossNative/CNMatcher/CNMatcher.h>
#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/Commands/AddCommand/AddingHierarchicModel.h>
#include <CrossViews/Commands/AddCommand/AddCommand.h>

AddActionPtr AddAction::getNewInstance(CBCommandInvokerPtr invoker,
                                       AddingHierarchicModelPtr model,
                                       SelectionModelPtr selectionModel,
                                       CreateComponentStrategyPtr componentStrategy,
                                       CNMatcherPtr matcher) {
    return AddActionPtr(new AddAction(invoker, model, selectionModel, componentStrategy, matcher));
}

AddAction::~AddAction() {}

AddAction::AddAction(CBCommandInvokerPtr invoker,
                     AddingHierarchicModelPtr model,
                     SelectionModelPtr selectionModel,
                     CreateComponentStrategyPtr componentStrategy,
                     CNMatcherPtr matcher)
        : invoker(invoker), model(model), selectionModel(selectionModel),
          componentStrategy(componentStrategy), matcher(matcher) {}

void AddAction::execute() {
    CNComponentPtr component;
    try {
        component = componentStrategy->createComponent();
        invoker->invoke(makeCommand(model, getInsertingIndex(), component));
    } catch (CreationCanceledException& e) {}
}

CBCommandPtr AddAction::makeCommand(AddingHierarchicModelPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return AddCommand::getNewInstance(model, index, component);
}

CNHierarchyIndex AddAction::getInsertingIndex() {
    if(selectionModel->hasSelection() && matcher->matches(model->retrieve(selectionModel->getSelectedIndex())))
        return selectionModel->getSelectedIndex();

    return CNHierarchyIndex();
}
