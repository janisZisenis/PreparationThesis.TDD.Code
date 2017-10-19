#include "MenuEntryPresenter.h"
#include "MenuEntryView.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearance.h>
#include <CodeBase/CBTransAction/CBTransAction.h>

MenuEntryPresenterPtr MenuEntryPresenter::getNewInstance(MenuEntryViewPtr view,
                                                       CBTransActionAppearancePtr appearance,
                                                       CBTransActionPtr action) {
    return MenuEntryPresenterPtr(new MenuEntryPresenter(view, appearance, action));
}
MenuEntryPresenter::~MenuEntryPresenter() {}
MenuEntryPresenter::MenuEntryPresenter(MenuEntryViewPtr view,
                                     CBTransActionAppearancePtr appearance,
                                     CBTransActionPtr action)
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

void MenuEntryPresenter::onAction() {
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
