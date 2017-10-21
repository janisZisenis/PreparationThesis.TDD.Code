//#include "RemoveCommand.h"
//#include "../../HierarchicModel/API/InsertingHierarchicModel.h"
//
//RemoveCommandPtr RemoveCommand::getNewInstance(InsertingHierarchicModelPtr model, CCore::HierarchyIndex index) {
//    return RemoveCommandPtr(new RemoveCommand(model, index));
//}
//
//RemoveCommand::~RemoveCommand() {
//
//}
//
//RemoveCommand::RemoveCommand(InsertingHierarchicModelPtr model, CCore::HierarchyIndex index)
//        : model(model), index(index), pair(model->retrieve(index)) {}
//
//void RemoveCommand::execute() {
//    model->remove(index.parent(), index.childPosition());
//}
//
//void RemoveCommand::undo() {
//    model->insert(pair, index.parent(), index.childPosition());
//}
