#ifndef CROSSVIEWS_MENUENTRYPRESENTER_H
#define CROSSVIEWS_MENUENTRYPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include "MenuEntryListener.h"

class MenuEntryView;
class CBTransActionAppearance;
class CBTransAction;

class MenuEntryPresenter;
typedef std::shared_ptr<MenuEntryPresenter> MenuEntryPresenterPtr;

class MenuEntryPresenter : public CBObserver, public virtual CNVisitable, public MenuEntryListener {
public:
    static MenuEntryPresenterPtr getNewInstance(std::shared_ptr<MenuEntryView> view,
                                               std::shared_ptr<CBTransActionAppearance> appearance,
                                               std::shared_ptr<CBTransAction> action);
    virtual ~MenuEntryPresenter();
private:
    MenuEntryPresenter(std::shared_ptr<MenuEntryView> view,
                      std::shared_ptr<CBTransActionAppearance> appearance,
                      std::shared_ptr<CBTransAction> action);

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
    std::shared_ptr<CBTransActionAppearance> appearance;
    std::shared_ptr<CBTransAction> action;
};

#endif //CROSSVIEWS_MENUENTRYPRESENTER_H