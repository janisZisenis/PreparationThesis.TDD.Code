#include "QtMenuBar.h"
#include "QtMenuBarVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>

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

void QtMenuBar::addQAction(QAction* qAction) {
    menuBar->addAction(qAction);
}

void QtMenuBar::removeQAction(QAction* qAction) {
    menuBar->removeAction(qAction);
}

void QtMenuBar::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

QtMenuBarPtr QtMenuBar::me() {
    return this->shared_from_this();
}

