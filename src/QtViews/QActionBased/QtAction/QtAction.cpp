#include "QtAction.h"
#include "QtActionVisitor.h"
#include <QAction>
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include <CrossViews/MenuEntryPresenter/MenuEntryListener.h>

QtActionPtr QtAction::getNewInstance() {
    return QtActionPtr(new QtAction());
}

QtAction::~QtAction() {
    delete action;
}

QtAction::QtAction()
        : acceptor(CNAcceptorImp<QtActionVisitor, QtAction>::getNewInstance()),
          action (new QAction()) {
    connectToAction();
}

QAction *QtAction::getQAction() {
    return action;
}

void QtAction::connectToAction() {
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onTriggered(bool)));
}


void QtAction::setTitle(std::string newTitle) {
    action->setText(QString::fromStdString(newTitle));
}

void QtAction::check() {
    setChecked(true);
}

void QtAction::uncheck() {
    setChecked(false);
}

void QtAction::enable() {
    setEnbaled(true);
}

void QtAction::disable() {
    setEnbaled(false);
}

void QtAction::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

void QtAction::setChecked(bool checked) {
    action->setCheckable(checked);
    action->setChecked(checked);
}

void QtAction::setEnbaled(bool enabled) {
    action->setEnabled(enabled);
}

QtActionPtr QtAction::me() {
    return this->shared_from_this();
}

void QtAction::setListener(MenuEntryListenerPtr listener) {
    this->listener = listener;
}

void QtAction::onTriggered(bool checked) {
    if(listener)
        listener->onTriggered();
}
