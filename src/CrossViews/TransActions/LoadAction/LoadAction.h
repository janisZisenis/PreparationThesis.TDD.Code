#ifndef CROSSVIEWS_LOADACTION_H
#define CROSSVIEWS_LOADACTION_H

#include <CodeBase/CBTransAction/CBTransAction.h>

class ComponentLoader;
class CreateComponentStrategy;
class CNMatcher;

class LoadAction;
typedef std::shared_ptr<LoadAction> LoadActionPtr;

class LoadAction : public CBTransAction {
public:
    static LoadActionPtr getNewInstance(std::shared_ptr<ComponentLoader> componentLoader,
                                          std::shared_ptr<CreateComponentStrategy> componentStrategy,
                                          std::shared_ptr<CNMatcher> matcher);
    virtual ~LoadAction();
protected:
    LoadAction(std::shared_ptr<ComponentLoader> componentLoader,
                 std::shared_ptr<CreateComponentStrategy> componentStrategy,
                 std::shared_ptr<CNMatcher> matcher);

public:
    virtual void execute() override;

private:
    std::shared_ptr<ComponentLoader> componentLoader;
    std::shared_ptr<CreateComponentStrategy> componentStrategy;
    std::shared_ptr<CNMatcher> matcher;
};

#endif //CROSSVIEWS_LOADACTION_H