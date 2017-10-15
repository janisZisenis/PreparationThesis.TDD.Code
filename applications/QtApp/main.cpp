#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>

#include "QtViews/QtShell/QtShell.h"
#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtAction/QtAction.h"
#include "QtViews/QtMenu/QtMenu.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    QtShellPtr shell = QtShell::getNewInstance();
    QMenuBar* menuBar = new QMenuBar();
    QtSolutionExplorerPtr solutionExplorer = QtSolutionExplorer::getNewInstance();
    QtPropertiesExplorerPtr propertiesExplorer = QtPropertiesExplorer::getNewInstance();
    QtMenuPtr menu = QtMenu::getNewInstance("HelloWorld!");
    QtActionPtr helloAction = QtAction::getNewInstance();
    QtActionPtr worldAction = QtAction::getNewInstance();

    helloAction->setTitle("Hello");
    worldAction->setTitle("World");

    menu->addQAction(helloAction->getQAction());
    menu->addQAction(worldAction->getQAction());

    menuBar->addAction(menu->getQAction());

    shell->addQMenuBar(menuBar);
    shell->addQWidget(solutionExplorer->getQWidget(), LEFT);
    shell->addQWidget(propertiesExplorer->getQWidget(), RIGHT);


    return a.exec();
}