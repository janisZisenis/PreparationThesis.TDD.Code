#include "AddAction.h"
#include "CrossViews/TransActions/LoadAction/CreateComponentStrategy.h"
#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <Hierarchies/CNMatcher/CNMatcher.h>
#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/Commands/AddCommand/AddingHierarchicModel.h>
#include <CrossViews/Commands/AddCommand/AddCommand.h>

AddActionPtr AddAction::getNewInstance(CNCommandInvokerPtr invoker,
                                       AddingHierarchicModelPtr model,
                                       SelectionModelPtr selectionModel,
                                       CreateComponentStrategyPtr componentStrategy,
                                       CNMatcherPtr matcher) {
    return AddActionPtr(new AddAction(invoker, model, selectionModel, componentStrategy, matcher));
}

AddAction::~AddAction() {}

AddAction::AddAction(CNCommandInvokerPtr invoker,
                     AddingHierarchicModelPtr model,
                     SelectionModelPtr selectionModel,
                     CreateComponentStrategyPtr componentStrategy,
                     CNMatcherPtr matcher)
        : invoker(invoker), model(model), selectionModel(selectionModel),
          componentStrategy(componentStrategy), matcher(matcher) {}

void AddAction::execute() {
    try {
        CNComponentPtr component = componentStrategy->createComponent();
        invoker->invoke(makeCommand(model, getInsertingIndex(), component));
    } catch (CreationCanceledException& e) {}
}

CNCommandPtr AddAction::makeCommand(AddingHierarchicModelPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return AddCommand::getNewInstance(model, index, component);
}

CNHierarchyIndex AddAction::getInsertingIndex() {
    if(selectionModel->hasSelection() && matcher->matches(model->retrieve(selectionModel->getSelectedIndex())))
        return selectionModel->getSelectedIndex();

    return CNHierarchyIndex();
}
