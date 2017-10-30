#ifndef CROSSVIEWS_REMOVECOMMAND_H
#define CROSSVIEWS_REMOVECOMMAND_H

#include <CodeBase/CBCommand/CBCommand.h>
#include <CrossHierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;
class InsertingHierarchicModel;

class RemoveCommand;
typedef std::shared_ptr<RemoveCommand> RemoveCommandPtr;

class RemoveCommand : public CBCommand {
public:
    static RemoveCommandPtr getNewInstance(std::shared_ptr<InsertingHierarchicModel> model,
                                           CNHierarchyIndex index,
                                           std::shared_ptr<CNComponent> component);
    virtual ~RemoveCommand();
protected:
    RemoveCommand(std::shared_ptr<InsertingHierarchicModel> model,
                  CNHierarchyIndex index,
                  std::shared_ptr<CNComponent> component);

public:
    virtual void execute() override;
    virtual void undo() override;

private:
    std::shared_ptr<CNComponent> component;
    std::shared_ptr<InsertingHierarchicModel> model;
    CNHierarchyIndex index;
};

#endif //CROSSVIEWS_REMOVECOMMAND_H
