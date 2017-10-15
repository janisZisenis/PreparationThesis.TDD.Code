#include <QApplication>
#include <QMainWindow>

#include "QtPropertiesExplorer/QtPropertiesExplorer.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtPropertiesExplorerPtr propertiesExplorer = QtPropertiesExplorer::getNewInstance();
    QMainWindow* w = new QMainWindow();
    w->setCentralWidget(propertiesExplorer->getQWidget());
    w->show();

    return a.exec();
}