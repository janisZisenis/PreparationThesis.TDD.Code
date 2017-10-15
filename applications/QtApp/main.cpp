#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include "QtPropertiesExplorer/QtPropertiesExplorer.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtPropertiesExplorerPtr propertiesExplorer = QtPropertiesExplorer::getNewInstance();
    QMainWindow* w = new QMainWindow();
    w->setCentralWidget(static_cast<QWidget*>(propertiesExplorer->getGraphicRepresentation()));
    w->show();

    return a.exec();
}