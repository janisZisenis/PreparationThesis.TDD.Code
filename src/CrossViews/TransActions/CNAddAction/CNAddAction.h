#ifndef CROSSNATIVE_ADDACTION_H
#define CROSSNATIVE_ADDACTION_H

#include <Base/CNTransAction/CNTransAction.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNCommand;
class CNCommandInvoker;

class CNMatcher;
class CNComponent;
class CNVisitable;
class CNComposer;
class CNCreateComponentStrategy;

class CNSelectionModel;
class CNComponentAdder;

class CNAddAction;
typedef std::shared_ptr<CNAddAction> CNAddActionPtr;

class CNAddAction : public CNTransAction {
public:
    static CNAddActionPtr getNewInstance(std::shared_ptr<CNCommandInvoker> invoker,
                                       std::shared_ptr<CNComponentAdder> model,
                                       std::shared_ptr<CNSelectionModel> selectionModel,
                                       std::shared_ptr<CNCreateComponentStrategy> componentStrategy,
                                       std::shared_ptr<CNMatcher> matcher);
    virtual ~CNAddAction();
protected:
    CNAddAction(std::shared_ptr<CNCommandInvoker> invoker,
              std::shared_ptr<CNComponentAdder> model,
              std::shared_ptr<CNSelectionModel> selectionModel,
              std::shared_ptr<CNCreateComponentStrategy> componentStrategy,
              std::shared_ptr<CNMatcher> matcher);
public:
    virtual void execute() override;

private:
    virtual std::shared_ptr<CNCommand> makeCommand(std::shared_ptr<CNComponentAdder> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);
    virtual CNHierarchyIndex getInsertingIndex();

private:
    std::shared_ptr<CNCommandInvoker> invoker;
    std::shared_ptr<CNComponentAdder> model;
    std::shared_ptr<CNSelectionModel> selectionModel;
    std::shared_ptr<CNCreateComponentStrategy> componentStrategy;
    std::shared_ptr<CNMatcher> matcher;
};

#endif //CROSSNATIVE_ADDACTION_H
