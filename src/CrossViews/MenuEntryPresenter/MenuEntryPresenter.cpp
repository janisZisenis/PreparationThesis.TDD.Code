#include "MenuEntryPresenter.h"
#include "MenuEntryView.h"
#include <Base/CNTransActionAppearance/CNTransActionAppearance.h>
#include <Base/CNTransAction/CNTransAction.h>

MenuEntryPresenterPtr MenuEntryPresenter::getNewInstance(MenuEntryViewPtr view,
                                                       CNTransActionAppearancePtr appearance,
                                                       CNTransActionPtr action) {
    return MenuEntryPresenterPtr(new MenuEntryPresenter(view, appearance, action));
}
MenuEntryPresenter::~MenuEntryPresenter() {}
MenuEntryPresenter::MenuEntryPresenter(MenuEntryViewPtr view,
                                     CNTransActionAppearancePtr appearance,
                                     CNTransActionPtr action)
        : view(view),
          appearance(appearance),
          action(action) {
    update();
}

void MenuEntryPresenter::update() {
    updateTitle();
    updateState();
    updateAccessibility();
}

void MenuEntryPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void MenuEntryPresenter::onTriggered() {
    action->execute();
}

void MenuEntryPresenter::updateState() {
    appearance->getState() == ON ? view->check() : view->uncheck();
}

void MenuEntryPresenter::updateAccessibility() {
    appearance->isAccessible() ? view->enable() : view->disable();
}

void MenuEntryPresenter::updateTitle() {
    view->setTitle(appearance->getTitle());
}
