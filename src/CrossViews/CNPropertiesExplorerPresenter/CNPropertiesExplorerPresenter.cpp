#include "CNPropertiesExplorerPresenter.h"
#include "CNPropertiesExplorerView.h"
#include "CrossViews/CNHierarchicModel/API/CNHierarchicComponentAccess.h"
#include "CrossViews/CNSelectionModel/CNSelectionModel.h"
#include <Hierarchies/CNComponent/CNComponent.h>

CNPropertiesExplorerPresenterPtr CNPropertiesExplorerPresenter::getNewInstance(CNPropertiesExplorerViewPtr view,
                                                                               CNHierarchicComponentAccessPtr modelAccess,
                                                                               CNSelectionModelPtr selectionModel) {
    return CNPropertiesExplorerPresenterPtr(new CNPropertiesExplorerPresenter(view, modelAccess, selectionModel));
}
CNPropertiesExplorerPresenter::~CNPropertiesExplorerPresenter() {}
CNPropertiesExplorerPresenter::CNPropertiesExplorerPresenter(CNPropertiesExplorerViewPtr view,
                                                             CNHierarchicComponentAccessPtr modelAccess,
                                                             CNSelectionModelPtr selectionModel)
        : view(view), modelAccess(modelAccess), selectionModel(selectionModel) {}
void CNPropertiesExplorerPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void CNPropertiesExplorerPresenter::update() {
    selectionModel->hasSelection() ? displayProperties() : clearProperties();
}

void CNPropertiesExplorerPresenter::clearProperties() {
    view->displayEmptyProperties();
}

void CNPropertiesExplorerPresenter::displayProperties() {
    CNHierarchyIndex selectedIndex = selectionModel->getSelectedIndex();
    CNVisitablePtr selectedVisitable = modelAccess->retrieve(selectedIndex);
    view->displayPropertiesFor(selectedVisitable);
}
