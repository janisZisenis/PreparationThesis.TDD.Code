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
    appearance->getState() == ON ? actionView->check() : actionView->uncheck();
}

void MenuEntryPresenter::update() {
    actionView->setAccessibility(appearance->isAccessible());
    actionView->setState(appearance->getState());
    actionView->setTitle(appearance->getTitle());
}

void MenuEntryPresenter::accept(CNVisitorPtr visitor) {
    actionView->accept(visitor);
}

void MenuEntryPresenter::onAction() {
    action->execute();
}
