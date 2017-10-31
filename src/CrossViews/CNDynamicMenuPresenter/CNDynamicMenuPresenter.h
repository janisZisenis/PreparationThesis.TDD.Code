#ifndef CROSSNATIVE_DYNAMICMENUPRESENTER_H
#define CROSSNATIVE_DYNAMICMENUPRESENTER_H

#include <Base/CNObserver/CNObserver.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>
#include <vector>

class CNComposer;
class CNMenuView;
class CNVisitableListProvider;

class CNDynamicMenuPresenter;
typedef std::shared_ptr<CNDynamicMenuPresenter> CNDynamicMenuPresenterPtr;

class CNDynamicMenuPresenter : public CNObserver, public virtual CNVisitable {
public:
    static CNDynamicMenuPresenterPtr getNewInstance(std::shared_ptr<CNMenuView> view,
                                                    std::shared_ptr<CNComposer> composer,
                                                    std::shared_ptr<CNVisitableListProvider> listProvider);
    virtual ~CNDynamicMenuPresenter();
private:
    CNDynamicMenuPresenter(std::shared_ptr<CNMenuView> view,
                         std::shared_ptr<CNComposer> composer,
                         std::shared_ptr<CNVisitableListProvider> listProvider);

public:
    virtual void accept(CNVisitorPtr visitor) override;
    virtual void update() override;

private:
    virtual void mountMenuEntries();
    virtual void dismountMenuEntries();
    void updateMenuEntries();

private:
    std::shared_ptr<CNMenuView> view;
    std::shared_ptr<CNComposer> composer;
    std::shared_ptr<CNVisitableListProvider> listProvider;

    std::vector< std::shared_ptr<CNVisitable> > menuEntries;
};

#endif //CROSSNATIVE_DYNAMICMENUPRESENTER_H