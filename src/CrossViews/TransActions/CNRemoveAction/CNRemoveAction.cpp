#include "CNRemoveAction.h"
#include "CrossViews/CNSelectionModel/CNSelectionModel.h"
#include <Base/CNCommandInvoker/CNCommandInvoker.h>
#include <Hierarchies/CNComponent/CNComponent.h>
#include "CrossViews/Commands/CNRemoveCommand/CNRemoveCommand.h"
#include "CrossViews/Commands/CNRemoveCommand/CNComponentInserter.h"

CNRemoveActionPtr CNRemoveAction::getNewInstance(CNSelectionModelPtr selectionModel,
                                                 CNComponentInserterPtr model,
                                                 CNCommandInvokerPtr invoker) {
    return CNRemoveActionPtr(new CNRemoveAction(selectionModel, model, invoker));
}

CNRemoveAction::~CNRemoveAction() {}

CNRemoveAction::CNRemoveAction(CNSelectionModelPtr selectionModel,
                               CNComponentInserterPtr model,
                               CNCommandInvokerPtr invoker)
        : selectionModel(selectionModel), model(model), invoker(invoker) {}

void CNRemoveAction::execute() {
    CNHierarchyIndex selectedIndex = selectionModel->getSelectedIndex();
    CNComponentPtr selectedComponent = model->retrieve(selectedIndex);
    CNCommandPtr command = makeCommand(model, selectedIndex, selectedComponent);

    invoker->invoke(command);
}

CNCommandPtr CNRemoveAction::makeCommand(CNComponentInserterPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return CNRemoveCommand::getNewInstance(model, index, component);
}
