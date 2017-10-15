#include "QtPropertiesExplorer.h"
#include "QtPropertiesModel.h"
#include <QTreeView>

QtPropertiesExplorerPtr QtPropertiesExplorer::getNewInstance() {
    return QtPropertiesExplorerPtr(new QtPropertiesExplorer());
}

QtPropertiesExplorer::~QtPropertiesExplorer() {
    delete tableView;
}

QtPropertiesExplorer::QtPropertiesExplorer()
        : tableView(new QTreeView()) {
    tableView->setWindowTitle("Properties Explorer");

    QtPropertiesModel* propertiesModel = new QtPropertiesModel();
    tableView->setModel(propertiesModel);
}

std::string QtPropertiesExplorer::getTitle() {
    return tableView->windowTitle().toStdString();
}

void QtPropertiesExplorer::toggleGUIVisibility() {
    tableView->setVisible(!tableView->isVisible());
}

bool QtPropertiesExplorer::isVisible() {
    return tableView->isVisible();
}

void QtPropertiesExplorer::displayEmptyProperties() {
    tableView->setModel(new QtPropertiesModel());
}

void QtPropertiesExplorer::displayProperties(QtPropertiesModel* model) {
    QAbstractItemModel* oldModel = tableView->model();
    tableView->setModel(model);
    delete oldModel;
}

QWidget* QtPropertiesExplorer::getQWidget() {
    return tableView;
}
