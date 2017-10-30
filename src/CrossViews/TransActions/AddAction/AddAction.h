#ifndef CROSSVIEWS_ADDACTION_H
#define CROSSVIEWS_ADDACTION_H

#include <Base/CNTransAction/CNTransAction.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNCommand;
class CNCommandInvoker;

class CNMatcher;
class CNComponent;
class CNVisitable;
class CNComposer;
class CreateComponentStrategy;

class SelectionModel;
class AddingHierarchicModel;

class AddAction;
typedef std::shared_ptr<AddAction> AddActionPtr;

class AddAction : public CNTransAction {
public:
    static AddActionPtr getNewInstance(std::shared_ptr<CNCommandInvoker> invoker,
                                       std::shared_ptr<AddingHierarchicModel> model,
                                       std::shared_ptr<SelectionModel> selectionModel,
                                       std::shared_ptr<CreateComponentStrategy> componentStrategy,
                                       std::shared_ptr<CNMatcher> matcher);
    virtual ~AddAction();
protected:
    AddAction(std::shared_ptr<CNCommandInvoker> invoker,
              std::shared_ptr<AddingHierarchicModel> model,
              std::shared_ptr<SelectionModel> selectionModel,
              std::shared_ptr<CreateComponentStrategy> componentStrategy,
              std::shared_ptr<CNMatcher> matcher);
public:
    virtual void execute() override;

private:
    virtual std::shared_ptr<CNCommand> makeCommand(std::shared_ptr<AddingHierarchicModel> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);
    virtual CNHierarchyIndex getInsertingIndex();

private:
    std::shared_ptr<CNCommandInvoker> invoker;
    std::shared_ptr<AddingHierarchicModel> model;
    std::shared_ptr<SelectionModel> selectionModel;
    std::shared_ptr<CreateComponentStrategy> componentStrategy;
    std::shared_ptr<CNMatcher> matcher;
};

#endif //CROSSVIEWS_ADDACTION_H
