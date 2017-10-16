#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>

#include <CrossNative/CNDynamicHierarchy/CNDynamicHierarchy.h>
#include <CrossNative/CNComposable/CNComposable.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include <CrossNative/CNComposer/CNVisitingComposer.h>
#include <CrossNative/CNMatcher/CNNullMatcher.h>
#include <CrossNative/CNMatcher/CNTypeMatcher.h>

#include "QtViews/QtShell/QtShell.h"
#include "QtViews/QtShell/Visitors/QtShellComposingVisitor.h"
#include "QtViews/QtShell/Visitors/QtShellDecomposingVisitor.h"
#include "QtViews/QtShell/Visitors/QtShellNullVisitor.h"

#include "QtViews/QtPropertiesExplorer/QtPropertiesExplorer.h"
#include "QtViews/QtSolutionExplorer/QtSolutionExplorer.h"
#include "QtViews/QtMenu/QtMenu.h"
#include "QtViews/QtMenuBar/QtMenuBar.h"
#include "QtViews/QtAction/QtAction.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

//    QtMenuPtr menu = QtMenu::getNewInstance("HelloWorld!");
//    QtActionPtr helloAction = QtAction::getNewInstance();
//    QtActionPtr worldAction = QtAction::getNewInstance();
//
//    helloAction->setTitle("Hello");
//    worldAction->setTitle("World");
//    menuBar->getQMenuBar()->addAction(menu->getQAction());
//
//    menu->addQAction(helloAction->getQAction());
//    menu->addQAction(worldAction->getQAction());
//
//    menuBar->addAction(menu->getQAction());
//
//    shell->addQMenuBar(menuBar);
//    shell->addQWidget(solutionExplorer->getQWidget(), LEFT);
//    shell->addQWidget(propertiesExplorer->getQWidget(), RIGHT);

    QtShellPtr shell = QtShell::getNewInstance();
    CNVisitingComposerPtr shellComposer = CNVisitingComposer::getNewInstance(QtShellComposingVisitor::getNewInstance(shell), QtShellDecomposingVisitor::getNewInstance(shell));

    CNDynamicHierarchyPtr viewHierarchy = CNDynamicHierarchy::getNewInstance();
    viewHierarchy->load(CNComposable::getNewInstance(shell, shellComposer), CNNullMatcher::getNewInstance());
    viewHierarchy->load(CNComposable::getNewInstance(QtSolutionExplorer::getNewInstance(), CNNullComposer::getNewInstance()), CNTypeMatcher::getNewInstance(QtShellNullVisitor::getNewInstance()));
    viewHierarchy->load(CNComposable::getNewInstance(QtPropertiesExplorer::getNewInstance(), CNNullComposer::getNewInstance()), CNTypeMatcher::getNewInstance(QtShellNullVisitor::getNewInstance()));
    viewHierarchy->load(CNComposable::getNewInstance(QtMenuBar::getNewInstance(), CNNullComposer::getNewInstance()), CNTypeMatcher::getNewInstance(QtShellNullVisitor::getNewInstance()));

    return a.exec();
}