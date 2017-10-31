#include "CNAddCommand.h"
#include "CNComponentAdder.h"
#include <Hierarchies/CNComponent/CNComponent.h>

CNAddCommandPtr CNAddCommand::getNewInstance(std::shared_ptr<CNComponentAdder> model, CNHierarchyIndex index,
                                        std::shared_ptr<CNComponent> component) {
    return CNAddCommandPtr(new CNAddCommand(model, index, component));
}

CNAddCommand::~CNAddCommand() {

}

CNAddCommand::CNAddCommand(std::shared_ptr<CNComponentAdder> model, CNHierarchyIndex index,
                       std::shared_ptr<CNComponent> component)
        : component(component), index(index), model(model) {}

void CNAddCommand::execute() {
    model->add(component, index);
}

void CNAddCommand::undo() {
    model->remove(component, index);
}
