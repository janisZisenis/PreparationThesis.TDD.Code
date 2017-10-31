#ifndef CROSSNATIVE_ADDCOMMAND_H
#define CROSSNATIVE_ADDCOMMAND_H

#include <Base/CNCommandInvoker/CNCommand.h>
#include <Hierarchies/CNHierarchy/CNHierarchy.h>

class CNComponentAdder;
class CNComponent;

class CNAddCommand;
typedef std::shared_ptr<CNAddCommand> CNAddCommandPtr;

class CNAddCommand : public CNCommand {
public:
    static CNAddCommandPtr getNewInstance(std::shared_ptr<CNComponentAdder> model,
                                        CNHierarchyIndex index,
                                        std::shared_ptr<CNComponent> component);
    virtual ~CNAddCommand();
protected:
    CNAddCommand(std::shared_ptr<CNComponentAdder> model,
               CNHierarchyIndex index,
               std::shared_ptr<CNComponent> component);

public:
    virtual void execute() override;
    virtual void undo() override;

private:
    std::shared_ptr<CNComponent> component;
    CNHierarchyIndex index;
    std::shared_ptr<CNComponentAdder> model;
};

#endif //CROSSNATIVE_ADDCOMMAND_H
