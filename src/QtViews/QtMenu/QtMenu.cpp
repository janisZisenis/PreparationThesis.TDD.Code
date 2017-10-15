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

void QtMenu::initializeAction() {
    action->setMenu(menu);
}

void QtMenu::initializeMenu() {
    menu->addAction(emptyAction);
}

void QtMenu::initializeEmptyAction() {
    emptyAction->setDisabled(true);
}

QAction* QtMenu::getQAction() {
    return action;
}