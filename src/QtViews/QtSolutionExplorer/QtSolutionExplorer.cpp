#include <QWidget>
#include <QTreeView>
#include <QPushButton>
#include "QtSolutionExplorer.h"
#include "QtSolutionModel.h"
#include <QVBoxLayout>
#include "QtSolutionItem.h"

QtSolutionExplorerPtr QtSolutionExplorer::getNewInstance() {
    return QtSolutionExplorerPtr(new QtSolutionExplorer());
}

QtSolutionExplorer::~QtSolutionExplorer() {
    delete treeView;
    delete solutionModel;
}

QtSolutionExplorer::QtSolutionExplorer()
        : treeView(new QTreeView()), deselectButton(new QPushButton("Clear Selection")), widget(new QWidget()),
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

void QtSolutionExplorer::removeIndex(QModelIndex& index) {
    treeView->setCurrentIndex(QModelIndex());
    solutionModel->deleteIndex(index.parent(), index.row());

    treeView->setCurrentIndex(index);
}

QModelIndex QtSolutionExplorer::getSelectedIndex() {
    return treeView->currentIndex();
}

void QtSolutionExplorer::insertItem(std::shared_ptr<QtSolutionItem> item, QModelIndex index, int childPos) {
    solutionModel->insertItem(item, index, childPos);
}

void QtSolutionExplorer::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {}

void QtSolutionExplorer::onDeselectClicked() {
    treeView->setCurrentIndex(QModelIndex());
}
