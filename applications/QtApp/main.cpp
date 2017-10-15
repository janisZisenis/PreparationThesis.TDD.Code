#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>

#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtAction/QtAction.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtSolutionExplorerPtr solutionExplorer = QtSolutionExplorer::getNewInstance();
    QtPropertiesExplorerPtr propertiesExplorer = QtPropertiesExplorer::getNewInstance();

    QMainWindow* window = new QMainWindow();
    window->setCentralWidget(propertiesExplorer->getQWidget());
    window->show();

    QtActionPtr helloAction = QtAction::getNewInstance();
    helloAction->setTitle("Hello");
    QtActionPtr worldAction = QtAction::getNewInstance();
    worldAction->setTitle("World");


    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu();
    menu->setTitle("HelloWorld!");
    menuBar->addMenu(menu);
    window->setMenuBar(menuBar);

    menu->addAction(helloAction->getQAction());
    menu->addAction(worldAction->getQAction());

    return a.exec();
}