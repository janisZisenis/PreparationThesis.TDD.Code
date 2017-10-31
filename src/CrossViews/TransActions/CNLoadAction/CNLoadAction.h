#ifndef CROSSNATIVE_LOADACTION_H
#define CROSSNATIVE_LOADACTION_H

#include <Base/CNTransAction/CNTransAction.h>

class CNComponentLoader;
class CNCreateComponentStrategy;
class CNMatcher;

class CNLoadAction;
typedef std::shared_ptr<CNLoadAction> CNLoadActionPtr;

class CNLoadAction : public CNTransAction {
public:
    static CNLoadActionPtr getNewInstance(std::shared_ptr<CNComponentLoader> componentLoader,
                                          std::shared_ptr<CNCreateComponentStrategy> componentStrategy,
                                          std::shared_ptr<CNMatcher> matcher);
    virtual ~CNLoadAction();
protected:
    CNLoadAction(std::shared_ptr<CNComponentLoader> componentLoader,
                 std::shared_ptr<CNCreateComponentStrategy> componentStrategy,
                 std::shared_ptr<CNMatcher> matcher);

public:
    virtual void execute() override;

private:
    std::shared_ptr<CNComponentLoader> componentLoader;
    std::shared_ptr<CNCreateComponentStrategy> componentStrategy;
    std::shared_ptr<CNMatcher> matcher;
};

#endif //CROSSNATIVE_LOADACTION_H