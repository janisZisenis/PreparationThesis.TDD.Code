#include "MenuEntryPresenter.h"
#include "MenuEntryView.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearance.h>
#include <CodeBase/CBTransAction/CBTransAction.h>

MenuEntryPresenterPtr MenuEntryPresenter::getNewInstance(MenuEntryViewPtr actionView,
                                                       CBTransActionAppearancePtr appearance,
                                                       CBTransActionPtr action) {
    return MenuEntryPresenterPtr(new MenuEntryPresenter(actionView, appearance, action));
}
MenuEntryPresenter::~MenuEntryPresenter() {}
MenuEntryPresenter::MenuEntryPresenter(MenuEntryViewPtr actionView,
                                     CBTransActionAppearancePtr appearance,
                                     CBTransActionPtr action)
        : actionView(actionView),
          appearance(appearance),
          action(action) {
    update();
    updateState();
    updateAccessibility();
}

void MenuEntryPresenter::update() {
    actionView->setAccessibility(appearance->isAccessible());
    actionView->setState(appearance->getState());
    actionView->setTitle(appearance->getTitle());
    updateState();
}

void MenuEntryPresenter::accept(CNVisitorPtr visitor) {
    actionView->accept(visitor);
}

void MenuEntryPresenter::onAction() {
    action->execute();
}

void MenuEntryPresenter::updateState() {
    appearance->getState() == ON ? actionView->check() : actionView->uncheck();
}

void MenuEntryPresenter::updateAccessibility() {
    appearance->isAccessible() ? actionView->enable() : actionView->disable();
}
