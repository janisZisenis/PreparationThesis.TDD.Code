#include "QtSolutionExplorer.h"
#include "QtSolutionExplorerVisitor.h"
#include <QtWidgets>

#include "QtSolutionItem.h"
#include "QtSolutionModel.h"

#include <CrossNative/CNAcceptor/CNAcceptorImp.h>

QtSolutionExplorerPtr QtSolutionExplorer::getNewInstance() {
    return QtSolutionExplorerPtr(new QtSolutionExplorer());
}

QtSolutionExplorer::~QtSolutionExplorer() {
    delete treeView;
    delete solutionModel;
}

QtSolutionExplorer::QtSolutionExplorer()
        : acceptor(CNAcceptorImp<QtSolutionExplorerVisitor, QtSolutionExplorer>::getNewInstance()),
          treeView(new QTreeView()), deselectButton(new QPushButton("Clear Selection")), widget(new QWidget()),
          solutionModel(new QtSolutionModel()) {
    widget->setWindowTitle("Solution Explorer");
    treeView->setModel(solutionModel);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(deselectButton);
    layout->addWidget(treeView);
    widget->setLayout(layout);

    connect(treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
            this, SLOT(onSelectionChanged (const QItemSelection&, const QItemSelection&)));

    connect(deselectButton, SIGNAL(clicked()), this, SLOT(onDeselectClicked()));
}

QWidget *QtSolutionExplorer::getQWidget() {
    return widget;
}

std::string QtSolutionExplorer::getTitle() {
    return widget->windowTitle().toStdString();
}

bool QtSolutionExplorer::isVisible() {
    return widget->isVisible();
}

void QtSolutionExplorer::toggleVisibility() {
    widget->setVisible(!widget->isVisible());
}

void QtSolutionExplorer::removeIndex(const QModelIndex &index) {
    treeView->setCurrentIndex(QModelIndex());
    solutionModel->deleteIndex(index.parent(), index.row());

    treeView->setCurrentIndex(index);
}

QModelIndex QtSolutionExplorer::getSelectedIndex() {
    return treeView->currentIndex();
}

void QtSolutionExplorer::insertItem(std::shared_ptr<QtSolutionItem> item, const QModelIndex &index, int childPos) {
    solutionModel->insertItem(item, index, childPos);
}

void QtSolutionExplorer::accept(CNVisitorPtr visitor) {
    acceptor->accept(visitor, me());
}

QtSolutionExplorerPtr QtSolutionExplorer::me() {
    return this->shared_from_this();
}

void QtSolutionExplorer::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {}

void QtSolutionExplorer::onDeselectClicked() {
    treeView->setCurrentIndex(QModelIndex());
}


