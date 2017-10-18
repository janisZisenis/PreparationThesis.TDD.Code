#ifndef QTVIEWS_QTACTIONPRESENTER_H
#define QTVIEWS_QTACTIONPRESENTER_H

#include <memory>
#include <string>

class QtActionView;
class CBTransActionAppearance;

class QtActionPresenter;
typedef std::shared_ptr<QtActionPresenter> QtActionPresenterPtr;

class QtActionPresenter {
public:
    static QtActionPresenterPtr getNewInstance(std::shared_ptr<QtActionView> actionView, std::shared_ptr<CBTransActionAppearance> appearance);
    virtual ~QtActionPresenter();
private:
    QtActionPresenter(std::shared_ptr<QtActionView> actionView, std::shared_ptr<CBTransActionAppearance> appearance);

public:
    virtual void update();

private:
    std::shared_ptr<QtActionView> actionView;
    std::shared_ptr<CBTransActionAppearance> appearance;
};

#endif //QTVIEWS_QTACTIONPRESENTER_H