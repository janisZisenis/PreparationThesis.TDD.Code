#include "QtMenu.h"

#include <QAction>
#include <QMenu>

QtMenuPtr QtMenu::getNewInstance(std::string title) {
    return QtMenuPtr(new QtMenu(title));
}

QtMenu::~QtMenu() {
    delete emptyAction;
    delete menu;
    delete action;
}

QtMenu::QtMenu(std::string title)
        : emptyAction(new QAction("Empty")),
          action(new QAction(QString::fromStdString(title))),
          menu(new QMenu(QString::fromStdString(title))) {
    initializeEmptyAction();
    initializeMenu();
    initializeAction();

}

QAction* QtMenu::getQAction() {
    return action;
}

void QtMenu::addQAction(QAction *action) {
    if(menuContainsEmptyAction())
        removeEmptyActionFromMenu();

    addToMenu(action);
}
void QtMenu::removeQAction(QAction *action) {
    removeFromMenu(action);

    if(menuIsEmpty())
        addEmptyActionToMenu();
}

void QtMenu::initializeAction() {
    action->setMenu(menu);
}
void QtMenu::initializeMenu() {
    menu->addAction(emptyAction);
}
void QtMenu::initializeEmptyAction() {
    emptyAction->setDisabled(true);
}

void QtMenu::addToMenu(QAction *action) {
    menu->addAction(action);
}
void QtMenu::removeFromMenu(QAction *action) {
    menu->removeAction(action);
}

bool QtMenu::menuIsEmpty() {
    return menu->actions().size() == 0;
}
bool QtMenu::menuContainsEmptyAction() {
    return menu->actions().contains(emptyAction);
}
void QtMenu::addEmptyActionToMenu() {
    menu->addAction(emptyAction);
}
void QtMenu::removeEmptyActionFromMenu() {
    menu->removeAction(emptyAction);
}
