#include "AddCommand.h"
#include "AddingHierarchicModel.h"
#include <CrossHierarchies/CNComponent/CNComponent.h>

AddCommandPtr AddCommand::getNewInstance(std::shared_ptr<AddingHierarchicModel> model, CNHierarchyIndex index,
                                        std::shared_ptr<CNComponent> component) {
    return AddCommandPtr(new AddCommand(model, index, component));
}

AddCommand::~AddCommand() {

}

AddCommand::AddCommand(std::shared_ptr<AddingHierarchicModel> model, CNHierarchyIndex index,
                       std::shared_ptr<CNComponent> component)
        : component(component), index(index), model(model) {}

void AddCommand::execute() {
    model->add(component, index);
}

void AddCommand::undo() {
    model->remove(component, index);
}
