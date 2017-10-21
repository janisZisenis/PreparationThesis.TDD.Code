#include "AddCommand.h"
#include "CrossViews/HierarchicModel/API/AddingHierarchicModel.h"
#include <CrossNative/CNComponent/CNComponent.h>

AddCommandPtr AddCommand::getNewInstance(CNComponentPtr component, const CNHierarchyIndex index, AddingHierarchicModelPtr model) {
    return AddCommandPtr(new AddCommand(component, index, model));
}

AddCommand::~AddCommand() {

}

AddCommand::AddCommand(CNComponentPtr component, const CNHierarchyIndex index, AddingHierarchicModelPtr model)
        : component(component), index(index), model(model) {}

void AddCommand::execute() {
    model->add(component, index);
}

void AddCommand::undo() {
//    model->remove(component, index);
}
