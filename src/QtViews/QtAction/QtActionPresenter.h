#ifndef QTVIEWS_QTACTIONPRESENTER_H
#define QTVIEWS_QTACTIONPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

class QtActionView;
class CBTransActionAppearance;
class CBTransAction;

class QtActionPresenter;
typedef std::shared_ptr<QtActionPresenter> QtActionPresenterPtr;

class QtActionPresenter : public CBObserver, public virtual CNVisitable {
public:
    static QtActionPresenterPtr getNewInstance(std::shared_ptr<QtActionView> actionView,
                                               std::shared_ptr<CBTransActionAppearance> appearance,
                                               std::shared_ptr<CBTransAction> action);
    virtual ~QtActionPresenter();
private:
    QtActionPresenter(std::shared_ptr<QtActionView> actionView,
                      std::shared_ptr<CBTransActionAppearance> appearance,
                      std::shared_ptr<CBTransAction> action);

public:
    virtual void update() override;
    virtual void accept(CNVisitorPtr visitor) override;

    virtual void onAction();

private:
    std::shared_ptr<QtActionView> actionView;
    std::shared_ptr<CBTransActionAppearance> appearance;
    std::shared_ptr<CBTransAction> action;
};

#endif //QTVIEWS_QTACTIONPRESENTER_H