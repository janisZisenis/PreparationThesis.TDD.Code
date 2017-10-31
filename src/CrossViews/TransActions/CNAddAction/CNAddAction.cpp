#include "CNAddAction.h"
#include "CrossViews/TransActions/CNLoadAction/CNCreateComponentStrategy.h"
#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include <Hierarchies/CNMatcher/CNMatcher.h>
#include <CrossViews/CNSelectionModel/CNSelectionModel.h>
#include <CrossViews/Commands/CNAddCommand/CNComponentAdder.h>
#include <CrossViews/Commands/CNAddCommand/CNAddCommand.h>

CNAddActionPtr CNAddAction::getNewInstance(CNCommandInvokerPtr invoker,
                                       CNComponentAdderPtr model,
                                       CNSelectionModelPtr selectionModel,
                                       CNCreateComponentStrategyPtr componentStrategy,
                                       CNMatcherPtr matcher) {
    return CNAddActionPtr(new CNAddAction(invoker, model, selectionModel, componentStrategy, matcher));
}

CNAddAction::~CNAddAction() {}

CNAddAction::CNAddAction(CNCommandInvokerPtr invoker,
                         CNComponentAdderPtr model,
                         CNSelectionModelPtr selectionModel,
                         CNCreateComponentStrategyPtr componentStrategy,
                         CNMatcherPtr matcher)
        : invoker(invoker), model(model), selectionModel(selectionModel),
          componentStrategy(componentStrategy), matcher(matcher) {}

void CNAddAction::execute() {
    try {
        CNComponentPtr component = componentStrategy->createComponent();
        invoker->invoke(makeCommand(model, getInsertingIndex(), component));
    } catch (CreationCanceledException& e) {}
}

CNCommandPtr CNAddAction::makeCommand(CNComponentAdderPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return CNAddCommand::getNewInstance(model, index, component);
}

CNHierarchyIndex CNAddAction::getInsertingIndex() {
    if(selectionModel->hasSelection() && matcher->matches(model->retrieve(selectionModel->getSelectedIndex())))
        return selectionModel->getSelectedIndex();

    return CNHierarchyIndex();
}
