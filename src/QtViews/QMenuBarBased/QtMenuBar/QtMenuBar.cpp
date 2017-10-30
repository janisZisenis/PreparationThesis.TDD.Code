#include "QtMenuBar.h"
#include "QtMenuBarVisitor.h"
#include <Hierarchies/CNAcceptor/CNAcceptorImp.h>
#include "QtViews/QActionBased/QActionBased.h"

#include <QMenuBar>

QtMenuBarPtr QtMenuBar::getNewInstance() {
    return QtMenuBarPtr(new QtMenuBar());
}
QtMenuBar::~QtMenuBar() {
    delete menuBar;
}
QtMenuBar::QtMenuBar()
        : acceptor(CNAcceptorImp<QtMenuBarVisitor, QtMenuBar>::getNewInstance()),
          menuBar(new QMenuBar()) {}

QMenuBar *QtMenuBar::getQMenuBar() {
    return this->menuBar;
}

void QtMenuBar::addQAction(QActionBasedPtr qActionBased) {
    menuBar->addAction(qActionBased->getQAction());
}

void QtMenuBar::removeQAction(QActionBasedPtr qActionBased) {
    menuBar->removeAction(qActionBased->getQAction());
}

void QtMenuBar::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

QtMenuBarPtr QtMenuBar::me() {
    return this->shared_from_this();
}

