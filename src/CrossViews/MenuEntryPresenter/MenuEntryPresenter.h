#ifndef CROSSVIEWS_MENUENTRYPRESENTER_H
#define CROSSVIEWS_MENUENTRYPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

class MenuEntryView;
class CBTransActionAppearance;
class CBTransAction;

class MenuEntryPresenter;
typedef std::shared_ptr<MenuEntryPresenter> MenuEntryPresenterPtr;

class MenuEntryPresenter : public CBObserver, public virtual CNVisitable {
public:
    static MenuEntryPresenterPtr getNewInstance(std::shared_ptr<MenuEntryView> actionView,
                                               std::shared_ptr<CBTransActionAppearance> appearance,
                                               std::shared_ptr<CBTransAction> action);
    virtual ~MenuEntryPresenter();
private:
    MenuEntryPresenter(std::shared_ptr<MenuEntryView> actionView,
                      std::shared_ptr<CBTransActionAppearance> appearance,
                      std::shared_ptr<CBTransAction> action);

public:
    virtual void update() override;
    virtual void accept(CNVisitorPtr visitor) override;

    virtual void onAction();

private:
    virtual void updateState();
    virtual void updateAccessibility();

private:
    std::shared_ptr<MenuEntryView> actionView;
    std::shared_ptr<CBTransActionAppearance> appearance;
    std::shared_ptr<CBTransAction> action;
};

#endif //CROSSVIEWS_MENUENTRYPRESENTER_H