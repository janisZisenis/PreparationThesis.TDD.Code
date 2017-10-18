#include "QtActionPresenter.h"
#include "QtActionView.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearance.h>

QtActionPresenterPtr QtActionPresenter::getNewInstance(QtActionViewPtr actionView, CBTransActionAppearancePtr appearance) {
    return QtActionPresenterPtr(new QtActionPresenter(actionView, appearance));
}
QtActionPresenter::~QtActionPresenter() {}
QtActionPresenter::QtActionPresenter(QtActionViewPtr actionView, CBTransActionAppearancePtr appearance)
        : actionView(actionView),
          appearance(appearance) {}

void QtActionPresenter::update() {
    actionView->setAccessibility(appearance->isAccessible());
}
