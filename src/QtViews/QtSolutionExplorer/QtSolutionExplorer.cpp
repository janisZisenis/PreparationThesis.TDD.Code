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

void QtSolutionExplorer::removeIndex(const CNHierarchyIndex &index) {
    QModelIndex qIndex = solutionModel->transformToQModelIndex(index);
    treeView->setCurrentIndex(QModelIndex());
    solutionModel->deleteIndex(qIndex.parent(), qIndex.row());

    treeView->setCurrentIndex(qIndex);
}

CNHierarchyIndex QtSolutionExplorer::getSelectedIndex() {
    return solutionModel->transformToHierarchyIndex(treeView->currentIndex());
}

void QtSolutionExplorer::insertItem(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) {
    solutionModel->insertItem(makeItem(visitable), solutionModel->transformToQModelIndex(index), childPos);
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

QtSolutionItemPtr QtSolutionExplorer::makeItem(CNVisitablePtr visitable) {
    throw std::logic_error("Function not yet implemented");
    return nullptr;
}


