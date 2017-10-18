#ifndef QTVIEWS_QTACTIONPRESENTER_H
#define QTVIEWS_QTACTIONPRESENTER_H

#include <memory>
#include <string>

class QtActionView;

class QtMenuPresenter;
typedef std::shared_ptr<QtMenuPresenter> QtActionPresenterPtr;

class QtMenuPresenter {
public:
    static QtActionPresenterPtr getNewInstance(std::shared_ptr<QtActionView> menuView);
    virtual ~QtMenuPresenter();
private:
    QtMenuPresenter(std::shared_ptr<QtActionView> menuView);

public:
    virtual void update();

private:
    std::shared_ptr<QtActionView> menuView;
};

#endif //QTVIEWS_QTACTIONPRESENTER_H