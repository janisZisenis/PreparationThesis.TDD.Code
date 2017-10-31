#include "CNMenuEntryPresenter.h"
#include "CNMenuEntryView.h"
#include <Base/CNTransActionAppearance/CNTransActionAppearance.h>
#include <Base/CNTransAction/CNTransAction.h>

CNMenuEntryPresenterPtr CNMenuEntryPresenter::getNewInstance(CNMenuEntryViewPtr view,
                                                       CNTransActionAppearancePtr appearance,
                                                       CNTransActionPtr action) {
    return CNMenuEntryPresenterPtr(new CNMenuEntryPresenter(view, appearance, action));
}
CNMenuEntryPresenter::~CNMenuEntryPresenter() {}
CNMenuEntryPresenter::CNMenuEntryPresenter(CNMenuEntryViewPtr view,
                                     CNTransActionAppearancePtr appearance,
                                     CNTransActionPtr action)
        : view(view),
          appearance(appearance),
          action(action) {
    update();
}

void CNMenuEntryPresenter::update() {
    updateTitle();
    updateState();
    updateAccessibility();
}

void CNMenuEntryPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void CNMenuEntryPresenter::onTriggered() {
    action->execute();
}

void CNMenuEntryPresenter::updateState() {
    appearance->getState() == ON ? view->check() : view->uncheck();
}

void CNMenuEntryPresenter::updateAccessibility() {
    appearance->isAccessible() ? view->enable() : view->disable();
}

void CNMenuEntryPresenter::updateTitle() {
    view->setTitle(appearance->getTitle());
}
