#ifndef IRMB_ADDSTLFILEACTION_H
#define IRMB_ADDSTLFILEACTION_H

#include <CodeBase/CBTransAction/CBTransAction.h>
#include <CrossNative/CNHierarchy/CNHierarchyIndex.h>

class CBCommand;
class CBCommandInvoker;

class CNMatcher;
class CNComponent;
class CNVisitable;
class CNComposer;

class SelectionModel;
class FileFinder;
class AddingHierarchicModel;

class AddSTLFileAction;
typedef std::shared_ptr<AddSTLFileAction> AddSTLFileActionPtr;

class AddSTLFileAction : public CBTransAction {
public:
    static AddSTLFileActionPtr getNewInstance(std::shared_ptr<CBCommandInvoker> invoker,
                                              std::shared_ptr<AddingHierarchicModel> model,
                                              std::shared_ptr<SelectionModel> selectionModel,
                                              std::shared_ptr<CNMatcher> matcher,
                                              std::shared_ptr<FileFinder> fileFinder);
    virtual ~AddSTLFileAction();
protected:
    AddSTLFileAction(std::shared_ptr<CBCommandInvoker> invoker,
                     std::shared_ptr<AddingHierarchicModel> model,
                     std::shared_ptr<SelectionModel> selectionModel,
                     std::shared_ptr<CNMatcher> matcher,
                     std::shared_ptr<FileFinder> fileFinder);

public:
    virtual void execute() override;

protected:
    virtual std::shared_ptr<CNComponent> makeSTLFileComponent(std::string fileName);
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
    std::shared_ptr<FileFinder> fileFinder;
};

#endif //IRMB_ADDSTLFILEACTION_H
