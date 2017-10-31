#ifndef CROSSNATIVE_REMOVEACTION_H
#define CROSSNATIVE_REMOVEACTION_H


#include <Base/CNTransAction/CNTransAction.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNCommand;
class CNCommandInvoker;
class CNComponent;

class CNSelectionModel;
class CNComponentInserter;

class CNRemoveAction;
typedef std::shared_ptr<CNRemoveAction> CNRemoveActionPtr;

class CNRemoveAction : public CNTransAction {
public:
    static CNRemoveActionPtr getNewInstance(std::shared_ptr<CNSelectionModel> selectionModel,
                                          std::shared_ptr<CNComponentInserter> model,
                                          std::shared_ptr<CNCommandInvoker> invoker);
    virtual ~CNRemoveAction();
protected:
    CNRemoveAction(std::shared_ptr<CNSelectionModel> selectionModel,
                 std::shared_ptr<CNComponentInserter> model,
                 std::shared_ptr<CNCommandInvoker> invoker);

public:
    virtual void execute() override;

protected:
    virtual std::shared_ptr<CNCommand> makeCommand(std::shared_ptr<CNComponentInserter> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);

private:
    std::shared_ptr<CNSelectionModel> selectionModel;
    std::shared_ptr<CNComponentInserter> model;
    std::shared_ptr<CNCommandInvoker> invoker;
};

#endif //CROSSNATIVE_REMOVEACTION_H
