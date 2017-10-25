#ifndef CROSSVIEWS_MENUPRESENTER_H
#define CROSSVIEWS_MENUPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include <vector>

class CNComposer;
class MenuView;
class MenuEntryListProvider;

class DynamicMenuPresenter;
typedef std::shared_ptr<DynamicMenuPresenter> DynamicMenuPresenterPtr;

class DynamicMenuPresenter : public CBObserver, public virtual CNVisitable {
public:
    static DynamicMenuPresenterPtr getNewInstance(std::shared_ptr<MenuView> view,
                                                  std::shared_ptr<CNComposer> composer,
                                                  std::shared_ptr<MenuEntryListProvider> listProvider);
    virtual ~DynamicMenuPresenter();
private:
    DynamicMenuPresenter(std::shared_ptr<MenuView> view,
                         std::shared_ptr<CNComposer> composer,
                         std::shared_ptr<MenuEntryListProvider> listProvider);

public:
    virtual void accept(CNVisitorPtr visitor) override;
    virtual void update() override;

private:
    virtual void mountMenuEntries();
    virtual void dismountMenuEntries();
    void updateMenuEntries();

private:
    std::shared_ptr<MenuView> view;
    std::shared_ptr<CNComposer> composer;
    std::shared_ptr<MenuEntryListProvider> listProvider;

    std::vector< std::shared_ptr<CNVisitable> > menuEntries;
};

#endif //CROSSVIEWS_MENUPRESENTER_H