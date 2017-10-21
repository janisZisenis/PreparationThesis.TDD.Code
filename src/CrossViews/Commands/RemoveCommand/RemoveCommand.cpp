#include "RemoveCommand.h"
#include "InsertingHierarchicModel.h"
#include <CrossNative/CNComponent/CNComponent.h>

RemoveCommandPtr RemoveCommand::getNewInstance(InsertingHierarchicModelPtr model,
                                               const CNHierarchyIndex index,
                                               CNComponentPtr component) {
    return RemoveCommandPtr(new RemoveCommand(model, index, component));
}

RemoveCommand::~RemoveCommand() {

}

RemoveCommand::RemoveCommand(InsertingHierarchicModelPtr model,
                             const CNHierarchyIndex index,
                             CNComponentPtr component)
        : model(model), index(index), component(component) {}

void RemoveCommand::execute() {
    model->remove(index.parent(), index.childPosition());
}

void RemoveCommand::undo() {
    model->insert(component, index.parent(), index.childPosition());
}
