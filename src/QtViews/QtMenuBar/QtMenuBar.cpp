#include "QtMenuBar.h"

#include <QMenuBar>

QtMenuBarPtr QtMenuBar::getNewInstance() {
    return QtMenuBarPtr(new QtMenuBar());
}
QtMenuBar::~QtMenuBar() {
    delete menuBar;
}
QtMenuBar::QtMenuBar() : menuBar(new QMenuBar()) {}

QMenuBar *QtMenuBar::getQMenuBar() {
    return this->menuBar;
}

void QtMenuBar::addQAction(QAction* qAction) {
    menuBar->addAction(qAction);
}

void QtMenuBar::removeQAction(QAction* qAction) {
    menuBar->removeAction(qAction);
}