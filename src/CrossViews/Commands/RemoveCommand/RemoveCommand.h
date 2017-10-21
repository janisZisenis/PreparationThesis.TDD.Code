//#ifndef LViCE_REMOVECOMMAND_H
//#define LViCE_REMOVECOMMAND_H
//
//#include "CCore/CommandStack/Command.h"
//#include "CCore/Hierarchy/HierarchyIndex.h"
//
//class VisitableComposerPair;
//class InsertingHierarchicModel;
//
//class RemoveCommand;
//typedef std::shared_ptr<RemoveCommand> RemoveCommandPtr;
//
//class LViCE_EXPORT RemoveCommand : public CCore::Command {
//public:
//    static RemoveCommandPtr getNewInstance(std::shared_ptr<InsertingHierarchicModel> model, CCore::HierarchyIndex index);
//
//
//    virtual ~RemoveCommand();
//protected:
//    RemoveCommand(std::shared_ptr<InsertingHierarchicModel> model, CCore::HierarchyIndex index);
//
//public:
//    virtual void execute() override;
//    virtual void undo() override;
//
//private:
//    std::shared_ptr<VisitableComposerPair> pair;
//    std::shared_ptr<InsertingHierarchicModel> model;
//    CCore::HierarchyIndex index;
//};
//
//#endif //LViCE_REMOVECOMMAND_H
