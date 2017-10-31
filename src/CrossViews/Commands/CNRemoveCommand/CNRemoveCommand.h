#ifndef CROSSNATIVE_REMOVECOMMAND_H
#define CROSSNATIVE_REMOVECOMMAND_H

#include <Base/CNCommandInvoker/CNCommand.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNComponent;
class CNComponentInserter;

class CNRemoveCommand;
typedef std::shared_ptr<CNRemoveCommand> CNRemoveCommandPtr;

class CNRemoveCommand : public CNCommand {
public:
    static CNRemoveCommandPtr getNewInstance(std::shared_ptr<CNComponentInserter> model,
                                           CNHierarchyIndex index,
                                           std::shared_ptr<CNComponent> component);
    virtual ~CNRemoveCommand();
protected:
    CNRemoveCommand(std::shared_ptr<CNComponentInserter> model,
                  CNHierarchyIndex index,
                  std::shared_ptr<CNComponent> component);

public:
    virtual void execute() override;
    virtual void undo() override;

private:
    std::shared_ptr<CNComponent> component;
    std::shared_ptr<CNComponentInserter> model;
    CNHierarchyIndex index;
};

#endif //CROSSNATIVE_REMOVECOMMAND_H
