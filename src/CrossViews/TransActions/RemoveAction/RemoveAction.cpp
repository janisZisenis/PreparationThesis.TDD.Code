#include "RemoveAction.h"
#include "CrossViews/SelectionModel/SelectionModel.h"
#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include "CrossViews/Commands/RemoveCommand/RemoveCommand.h"
#include "CrossViews/Commands/RemoveCommand/InsertingHierarchicModel.h"

RemoveActionPtr RemoveAction::getNewInstance(SelectionModelPtr selectionModel,
                                             InsertingHierarchicModelPtr model,
                                             CNCommandInvokerPtr invoker) {
    return RemoveActionPtr(new RemoveAction(selectionModel, model, invoker));
}

RemoveAction::~RemoveAction() {}

RemoveAction::RemoveAction(SelectionModelPtr selectionModel,
                           InsertingHierarchicModelPtr model,
                           CNCommandInvokerPtr invoker)
        : selectionModel(selectionModel), model(model), invoker(invoker) {}

void RemoveAction::execute() {
    CNHierarchyIndex selectedIndex = selectionModel->getSelectedIndex();
    CNComponentPtr selectedComponent = model->retrieve(selectedIndex);
    CNCommandPtr command = makeCommand(model, selectedIndex, selectedComponent);

    invoker->invoke(command);
}

CNCommandPtr RemoveAction::makeCommand(InsertingHierarchicModelPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return RemoveCommand::getNewInstance(model, index, component);
}
