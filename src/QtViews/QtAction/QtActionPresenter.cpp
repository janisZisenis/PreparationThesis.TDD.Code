#include "QtActionPresenter.h"
#include "QtActionView.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearance.h>
#include <CodeBase/CBTransAction/CBTransAction.h>

QtActionPresenterPtr QtActionPresenter::getNewInstance(QtActionViewPtr actionView,
                                                       CBTransActionAppearancePtr appearance,
                                                       CBTransActionPtr action) {
    return QtActionPresenterPtr(new QtActionPresenter(actionView, appearance, action));
}
QtActionPresenter::~QtActionPresenter() {}
QtActionPresenter::QtActionPresenter(QtActionViewPtr actionView,
                                     CBTransActionAppearancePtr appearance,
                                     CBTransActionPtr action)
        : actionView(actionView),
          appearance(appearance),
          action(action) {}

void QtActionPresenter::update() {
    actionView->setAccessibility(appearance->isAccessible());
    actionView->setState(appearance->getState());
    actionView->setTitle(appearance->getTitle());
}

void QtActionPresenter::accept(CNVisitorPtr visitor) {
    actionView->accept(visitor);
}

void QtActionPresenter::onAction() {

}
