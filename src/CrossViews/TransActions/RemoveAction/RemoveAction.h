#ifndef CROSSVIEWS_REMOVEACTION_H
#define CROSSVIEWS_REMOVEACTION_H


#include <Base/CNTransAction/CNTransAction.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNCommand;
class CNCommandInvoker;
class CNComponent;

class SelectionModel;
class InsertingHierarchicModel;

class RemoveAction;
typedef std::shared_ptr<RemoveAction> RemoveActionPtr;

class RemoveAction : public CNTransAction {
public:
    static RemoveActionPtr getNewInstance(std::shared_ptr<SelectionModel> selectionModel,
                                          std::shared_ptr<InsertingHierarchicModel> model,
                                          std::shared_ptr<CNCommandInvoker> invoker);
    virtual ~RemoveAction();
protected:
    RemoveAction(std::shared_ptr<SelectionModel> selectionModel,
                 std::shared_ptr<InsertingHierarchicModel> model,
                 std::shared_ptr<CNCommandInvoker> invoker);

public:
    virtual void execute() override;

protected:
    virtual std::shared_ptr<CNCommand> makeCommand(std::shared_ptr<InsertingHierarchicModel> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);

private:
    std::shared_ptr<SelectionModel> selectionModel;
    std::shared_ptr<InsertingHierarchicModel> model;
    std::shared_ptr<CNCommandInvoker> invoker;
};

#endif //CROSSVIEWS_REMOVEACTION_H
