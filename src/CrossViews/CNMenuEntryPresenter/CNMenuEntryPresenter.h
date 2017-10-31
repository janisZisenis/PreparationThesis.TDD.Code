#ifndef CROSSNATIVE_MENUENTRYPRESENTER_H
#define CROSSNATIVE_MENUENTRYPRESENTER_H

#include <Base/CNObserver/CNObserver.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>
#include "CNMenuEntryListener.h"

class CNMenuEntryView;
class CNTransActionAppearance;
class CNTransAction;

class MenuEntryPresenter;
typedef std::shared_ptr<MenuEntryPresenter> CNMenuEntryPresenterPtr;

class MenuEntryPresenter : public CNObserver, public virtual CNVisitable, public CNMenuEntryListener {
public:
    static CNMenuEntryPresenterPtr getNewInstance(std::shared_ptr<CNMenuEntryView> view,
                                               std::shared_ptr<CNTransActionAppearance> appearance,
                                               std::shared_ptr<CNTransAction> action);
    virtual ~MenuEntryPresenter();
private:
    MenuEntryPresenter(std::shared_ptr<CNMenuEntryView> view,
                      std::shared_ptr<CNTransActionAppearance> appearance,
                      std::shared_ptr<CNTransAction> action);

public:
    virtual void update() override;
    virtual void accept(CNVisitorPtr visitor) override;

    virtual void onTriggered() override;

private:
    virtual void updateTitle();
    virtual void updateState();
    virtual void updateAccessibility();

private:
    std::shared_ptr<CNMenuEntryView> view;
    std::shared_ptr<CNTransActionAppearance> appearance;
    std::shared_ptr<CNTransAction> action;
};

#endif //CROSSNATIVE_MENUENTRYPRESENTER_H