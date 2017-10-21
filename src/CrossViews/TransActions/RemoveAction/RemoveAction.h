#ifndef CROSSVIEWS_REMOVEACTION_H
#define CROSSVIEWS_REMOVEACTION_H


#include <CodeBase/CBTransAction/CBTransAction.h>
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CBCommand;
class CBCommandInvoker;
class CNComponent;

class SelectionModel;
class InsertingHierarchicModel;

class RemoveAction;
typedef std::shared_ptr<RemoveAction> RemoveActionPtr;

class RemoveAction : public CBTransAction {
public:
    static RemoveActionPtr getNewInstance(std::shared_ptr<SelectionModel> selectionModel,
                                          std::shared_ptr<InsertingHierarchicModel> model,
                                          std::shared_ptr<CBCommandInvoker> invoker);
    virtual ~RemoveAction();
protected:
    RemoveAction(std::shared_ptr<SelectionModel> selectionModel,
                 std::shared_ptr<InsertingHierarchicModel> model,
                 std::shared_ptr<CBCommandInvoker> invoker);

public:
    virtual void execute() override;

protected:
    virtual std::shared_ptr<CBCommand> makeCommand(std::shared_ptr<InsertingHierarchicModel> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);

private:
    std::shared_ptr<SelectionModel> selectionModel;
    std::shared_ptr<InsertingHierarchicModel> model;
    std::shared_ptr<CBCommandInvoker> invoker;
};

#endif //CROSSVIEWS_REMOVEACTION_H
