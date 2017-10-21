#ifndef LVICE_ADDGRIDGENERATORACTION_H
#define LVICE_ADDGRIDGENERATORACTION_H

#include <CodeBase/CBTransAction/CBTransAction.h>
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CBCommand;
class CBCommandInvoker;

class CNMatcher;
class CNComponent;
class CNVisitable;
class CNComposer;

class SelectionModel;
class AddingHierarchicModel;

class AddGridGeneratorAction;
typedef std::shared_ptr<AddGridGeneratorAction> AddGridGeneratorActionPtr;

class AddGridGeneratorAction : public CBTransAction {
public:
    static AddGridGeneratorActionPtr getNewInstance(std::shared_ptr<CBCommandInvoker> invoker,
                                                    std::shared_ptr<AddingHierarchicModel> model,
                                                    std::shared_ptr<SelectionModel> selectionModel,
                                                    std::shared_ptr<CNMatcher> matcher);
    virtual ~AddGridGeneratorAction();
protected:
    AddGridGeneratorAction(std::shared_ptr<CBCommandInvoker> invoker,
                           std::shared_ptr<AddingHierarchicModel> model,
                           std::shared_ptr<SelectionModel> selectionModel,
                           std::shared_ptr<CNMatcher> matcher);
public:
    virtual void execute() override;

protected:
    virtual std::shared_ptr<CNComponent> makeGridGeneratorComponent();
    virtual std::shared_ptr<CBCommand> makeCommand(std::shared_ptr<AddingHierarchicModel> model,
                                                   CNHierarchyIndex index,
                                                   std::shared_ptr<CNComponent> component);
    virtual std::shared_ptr<CNComponent> makeComposable(std::shared_ptr<CNVisitable> visitable,
                                                        std::shared_ptr<CNComposer> composer);
private:
    std::shared_ptr<CBCommandInvoker> invoker;
    std::shared_ptr<AddingHierarchicModel> model;
    std::shared_ptr<SelectionModel> selectionModel;
    std::shared_ptr<CNMatcher> matcher;
};

#endif //LVICE_ADDGRIDGENERATORACTION_H
