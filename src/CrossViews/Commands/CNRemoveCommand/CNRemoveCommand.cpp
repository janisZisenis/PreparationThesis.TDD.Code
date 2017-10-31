#include "CNRemoveCommand.h"
#include "CNComponentInserter.h"
#include <Hierarchies/CNComponent/CNComponent.h>

CNRemoveCommandPtr CNRemoveCommand::getNewInstance(CNComponentInserterPtr model,
                                                   CNHierarchyIndex index,
                                                   CNComponentPtr component) {
    return CNRemoveCommandPtr(new CNRemoveCommand(model, index, component));
}

CNRemoveCommand::~CNRemoveCommand() {

}

CNRemoveCommand::CNRemoveCommand(CNComponentInserterPtr model,
                                 CNHierarchyIndex index,
                                 CNComponentPtr component)
        : model(model), index(index), component(component) {}

void CNRemoveCommand::execute() {
    model->remove(index.parent(), index.childPosition());
}

void CNRemoveCommand::undo() {
    model->insert(component, index.parent(), index.childPosition());
}
