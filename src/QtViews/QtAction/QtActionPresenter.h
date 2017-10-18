#ifndef QTVIEWS_QTACTIONPRESENTER_H
#define QTVIEWS_QTACTIONPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

class QtActionView;
class CBTransActionAppearance;

class QtActionPresenter;
typedef std::shared_ptr<QtActionPresenter> QtActionPresenterPtr;

class QtActionPresenter : public CBObserver, public virtual CNVisitable {
public:
    static QtActionPresenterPtr getNewInstance(std::shared_ptr<QtActionView> actionView, std::shared_ptr<CBTransActionAppearance> appearance);
    virtual ~QtActionPresenter();
private:
    QtActionPresenter(std::shared_ptr<QtActionView> actionView, std::shared_ptr<CBTransActionAppearance> appearance);

public:
    virtual void update() override;
    virtual void accept(CNVisitorPtr visitor) override;

private:
    std::shared_ptr<QtActionView> actionView;
    std::shared_ptr<CBTransActionAppearance> appearance;
};

#endif //QTVIEWS_QTACTIONPRESENTER_H