#include "QtMenu.h"
#include "QtMenuVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include <CrossNative/CNTagged/CNTaggedVisitor.h>
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
        : typeAcceptor(CNAcceptorImp<QtMenuVisitor, QtMenu>::getNewInstance()),
          tagAcceptor(CNAcceptorImp<CNTaggedVisitor, CNTagged>::getNewInstance()),
          emptyAction(new QAction("Empty")),
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
    addEmptyActionToMenu();
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
    removeFromMenu(emptyAction);
}

void QtMenu::accept(CNVisitorPtr visitor) {
    try {
        typeAcceptor->accept(visitor, me());
    } catch(CNVisitableVisitorMismatchException &e) {
        tagAcceptor->accept(visitor, me());
    }
}

void QtMenu::setTag(std::string tag) {
    this->tag = tag;
}
std::string QtMenu::getTag() {
    return tag;
}

QtMenuPtr QtMenu::me() {
    return this->shared_from_this();
}
