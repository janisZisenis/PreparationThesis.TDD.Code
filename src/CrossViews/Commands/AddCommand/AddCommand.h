#ifndef CROSSVIEWS_ADDCOMMAND_H
#define CROSSVIEWS_ADDCOMMAND_H

#include <CodeBase/CBCommand/CBCommand.h>
#include <CrossNative/CNHierarchy/CNHierarchy.h>

class AddingHierarchicModel;
class CNComponent;

class AddCommand;
typedef std::shared_ptr<AddCommand> AddCommandPtr;

class AddCommand : public CBCommand {
public:
    static AddCommandPtr getNewInstance(std::shared_ptr<AddingHierarchicModel> model,
                                        const CNHierarchyIndex index,
                                        std::shared_ptr<CNComponent> component);
    virtual ~AddCommand();
protected:
    AddCommand(std::shared_ptr<AddingHierarchicModel> model,
               const CNHierarchyIndex index,
               std::shared_ptr<CNComponent> component);

public:
    virtual void execute() override;
    virtual void undo() override;

private:
    std::shared_ptr<CNComponent> component;
    CNHierarchyIndex index;
    std::shared_ptr<AddingHierarchicModel> model;
};

#endif //CROSSVIEWS_ADDCOMMAND_H
