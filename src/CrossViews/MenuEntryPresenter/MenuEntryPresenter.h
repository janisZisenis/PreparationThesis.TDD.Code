#ifndef CROSSVIEWS_MENUENTRYPRESENTER_H
#define CROSSVIEWS_MENUENTRYPRESENTER_H

#include <Base/CNObserver/CNObserver.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>
#include "MenuEntryListener.h"

class MenuEntryView;
class CNTransActionAppearance;
class CNTransAction;

class MenuEntryPresenter;
typedef std::shared_ptr<MenuEntryPresenter> MenuEntryPresenterPtr;

class MenuEntryPresenter : public CNObserver, public virtual CNVisitable, public MenuEntryListener {
public:
    static MenuEntryPresenterPtr getNewInstance(std::shared_ptr<MenuEntryView> view,
                                               std::shared_ptr<CNTransActionAppearance> appearance,
                                               std::shared_ptr<CNTransAction> action);
    virtual ~MenuEntryPresenter();
private:
    MenuEntryPresenter(std::shared_ptr<MenuEntryView> view,
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
    std::shared_ptr<MenuEntryView> view;
    std::shared_ptr<CNTransActionAppearance> appearance;
    std::shared_ptr<CNTransAction> action;
};

#endif //CROSSVIEWS_MENUENTRYPRESENTER_H