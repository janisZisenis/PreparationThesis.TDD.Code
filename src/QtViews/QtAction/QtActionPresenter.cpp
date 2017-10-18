#include "QtActionPresenter.h"
#include "QtActionView.h"

QtActionPresenterPtr QtMenuPresenter::getNewInstance(QtActionViewPtr menuView) {
    return QtActionPresenterPtr(new QtMenuPresenter(menuView));
}
QtMenuPresenter::~QtMenuPresenter() {}
QtMenuPresenter::QtMenuPresenter(QtActionViewPtr menuView) : menuView(menuView) {}

void QtMenuPresenter::update() {

}
