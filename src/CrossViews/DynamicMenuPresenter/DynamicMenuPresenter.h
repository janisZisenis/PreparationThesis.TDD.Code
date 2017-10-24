#ifndef CROSSVIEWS_MENUPRESENTER_H
#define CROSSVIEWS_MENUPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

class CNComposer;
class MenuView;

class DynamicMenuPresenter;
typedef std::shared_ptr<DynamicMenuPresenter> DynamicMenuPresenterPtr;

class DynamicMenuPresenter : public CBObserver, public virtual CNVisitable {
public:
    static DynamicMenuPresenterPtr getNewInstance(std::shared_ptr<MenuView> view, std::shared_ptr<CNComposer> composer);
    virtual ~DynamicMenuPresenter();
private:
    DynamicMenuPresenter(std::shared_ptr<MenuView> view, std::shared_ptr<CNComposer> composer);

public:
    virtual void accept(CNVisitorPtr visitor) override;
    virtual void update() override;

private:
    std::shared_ptr<MenuView> view;
    std::shared_ptr<CNComposer> composer;
};

#endif //CROSSVIEWS_MENUPRESENTER_H