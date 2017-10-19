#include "SolutionExplorerPresenter.h"
#include "SolutionExplorerView.h"

SolutionExplorerPresenterPtr SolutionExplorerPresenter::getNewInstance(SolutionExplorerViewPtr view) {
    return SolutionExplorerPresenterPtr(new SolutionExplorerPresenter(view));
}
SolutionExplorerPresenter::~SolutionExplorerPresenter() {}
SolutionExplorerPresenter::SolutionExplorerPresenter(SolutionExplorerViewPtr view) : view(view){}

void SolutionExplorerPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void SolutionExplorerPresenter::onRemove(const HierarchyIndex &index) {

}
