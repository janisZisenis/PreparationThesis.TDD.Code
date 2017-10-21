#include "QtPropertiesExplorer.h"
#include "QtPropertiesModel.h"
#include "QtPropertiesExplorerVisitor.h"
#include <CrossNative/CNAcceptor/CNAcceptorImp.h>
#include <QtWidgets>

QtPropertiesExplorerPtr QtPropertiesExplorer::getNewInstance() {
    return QtPropertiesExplorerPtr(new QtPropertiesExplorer());
}

QtPropertiesExplorer::~QtPropertiesExplorer() {
    delete tableView;
}

QtPropertiesExplorer::QtPropertiesExplorer()
        : acceptor(CNAcceptorImp<QtPropertiesExplorerVisitor, QtPropertiesExplorer>::getNewInstance()),
          tableView(new QTreeView()) {
    tableView->setWindowTitle("Properties Explorer");

    QtPropertiesModel* propertiesModel = new QtPropertiesModel();
    tableView->setModel(propertiesModel);
}

QWidget* QtPropertiesExplorer::getQWidget() {
    return tableView;
}

std::string QtPropertiesExplorer::getTitle() {
    return tableView->windowTitle().toStdString();
}

void QtPropertiesExplorer::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

void QtPropertiesExplorer::displayEmptyProperties() {
    tableView->setModel(new QtPropertiesModel());
}

void QtPropertiesExplorer::displayPropertiesFor(CNVisitablePtr visitable) {
    QAbstractItemModel* oldModel = tableView->model();
    tableView->setModel(makePropertiesModel(visitable));
    delete oldModel;
}

QtPropertiesExplorerPtr QtPropertiesExplorer::me() {
    return this->shared_from_this();
}

QtPropertiesModel *QtPropertiesExplorer::makePropertiesModel(CNVisitablePtr visitable) {
    throw std::logic_error("Function not yet implemented");
    return nullptr;
}
