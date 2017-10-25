#ifndef CROSSVIEWS_ADDACTION_H
#define CROSSVIEWS_ADDACTION_H

#include <CodeBase/CBTransAction/CBTransAction.h>
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CBCommand;
class CBCommandInvoker;

class CNMatcher;
class CNComponent;
class CNVisitable;
class CNComposer;
class CNCreateComponentStrategy;

class SelectionModel;
class AddingHierarchicModel;

class AddAction;
typedef std::shared_ptr<AddAction> AddActionPtr;

class AddAction : public CBTransAction {
public:
    static AddActionPtr getNewInstance(std::shared_ptr<CBCommandInvoker> invoker,
                                       std::shared_ptr<AddingHierarchicModel> model,
                                       std::shared_ptr<SelectionModel> selectionModel,
                                       std::shared_ptr<CNCreateComponentStrategy> componentStrategy,
                                       std::shared_ptr<CNMatcher> matcher);
    virtual ~AddAction();
protected:
    AddAction(std::shared_ptr<CBCommandInvoker> invoker,
              std::shared_ptr<AddingHierarchicModel> model,
              std::shared_ptr<SelectionModel> selectionModel,
              std::shared_ptr<CNCreateComponentStrategy> componentStrategy,
              std::shared_ptr<CNMatcher> matcher);
public:
    virtual void execute() override;

private:
    virtual std::shared_ptr<CBCommand> makeCommand(std::shared_ptr<AddingHierarchicModel> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);
    virtual CNHierarchyIndex getInsertingIndex();

private:
    std::shared_ptr<CBCommandInvoker> invoker;
    std::shared_ptr<AddingHierarchicModel> model;
    std::shared_ptr<SelectionModel> selectionModel;
    std::shared_ptr<CNCreateComponentStrategy> componentStrategy;
    std::shared_ptr<CNMatcher> matcher;
};

#endif //CROSSVIEWS_ADDACTION_H
