#include "QtAction.h"
#include <QAction>

QtActionPtr QtAction::getNewInstance() {
    return QtActionPtr(new QtAction());
}

QtAction::~QtAction() {
    delete action;
}

QtAction::QtAction() : action (new QAction()) {
    connectToAction();
}

QAction *QtAction::getQAction() {
    return action;
}

void QtAction::connectToAction() {
    connect(action, SIGNAL(hovered()), this, SLOT(onHovered()));
    connect(action, SIGNAL(changed()), this, SLOT(onChanged()));
    connect(action, SIGNAL(toggled(bool)), this, SLOT(onToggled(bool)));
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onTriggered(bool)));
}


void QtAction::setTitle(std::string newTitle) {
    action->setText(QString::fromStdString(newTitle));
}

void QtAction::setAccessibility(bool newAccessibility) {
    action->setEnabled(newAccessibility);
}

void QtAction::setChecked(bool checked) {
    action->setCheckable(checked);
    action->setChecked(checked);
}

void QtAction::onChanged() {}
void QtAction::onHovered() {}
void QtAction::onToggled(bool checked) {}
void QtAction::onTriggered(bool checked) {}


