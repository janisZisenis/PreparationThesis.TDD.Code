#include "CNSolutionExplorerPresenter.h"
#include "CNSolutionExplorerView.h"
#include "CrossViews/CNSelectionModel/CNSelectionModel.h"

CNSolutionExplorerPresenterPtr CNSolutionExplorerPresenter::getNewInstance(CNSolutionExplorerViewPtr view,
                                                                           CNSelectionModelPtr selectionModel) {
    return CNSolutionExplorerPresenterPtr(new CNSolutionExplorerPresenter(view, selectionModel));
}
CNSolutionExplorerPresenter::~CNSolutionExplorerPresenter() {}
CNSolutionExplorerPresenter::CNSolutionExplorerPresenter(CNSolutionExplorerViewPtr view,
                                                         CNSelectionModelPtr selectionModel)
        : view(view),
          selectionModel(selectionModel){}

void CNSolutionExplorerPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void CNSolutionExplorerPresenter::onRemove(const CNHierarchyIndex &index) {
    view->removeIndex(index);
}

void CNSolutionExplorerPresenter::onInsert(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) {
    view->insertItem(visitable, index, childPos);
}

void CNSolutionExplorerPresenter::onSelectionChanged() {
    selectionModel->setSelectedIndex(view->getSelectedIndex());
}
