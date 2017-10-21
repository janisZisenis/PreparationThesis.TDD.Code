#include "SolutionExplorerPresenter.h"
#include "SolutionExplorerView.h"
#include "CrossViews/SelectionModel/SelectionModel.h"

SolutionExplorerPresenterPtr SolutionExplorerPresenter::getNewInstance(SolutionExplorerViewPtr view,
                                                                       SelectionModelPtr selectionModel) {
    return SolutionExplorerPresenterPtr(new SolutionExplorerPresenter(view, selectionModel));
}
SolutionExplorerPresenter::~SolutionExplorerPresenter() {}
SolutionExplorerPresenter::SolutionExplorerPresenter(SolutionExplorerViewPtr view,
                                                     SelectionModelPtr selectionModel)
        : view(view),
          selectionModel(selectionModel){}

void SolutionExplorerPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void SolutionExplorerPresenter::onRemove(const CNHierarchyIndex &index) {
    view->removeIndex(index);
}

void SolutionExplorerPresenter::onInsert(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) {
    view->insertItem(visitable, index, childPos);
}

void SolutionExplorerPresenter::onSelectionChanged() {
    selectionModel->setSelectedIndex(view->getSelectedIndex());
}
