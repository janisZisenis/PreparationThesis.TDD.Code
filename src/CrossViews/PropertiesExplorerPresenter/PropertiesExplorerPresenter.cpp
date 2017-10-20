#include <Security/Security.h>
#include "PropertiesExplorerPresenter.h"
#include "PropertiesExplorerView.h"
#include "HierarchicModelAccess.h"
#include "CrossViews/SelecionModel/SelectionModel.h"

PropertiesExplorerPresenterPtr PropertiesExplorerPresenter::getNewInstance(PropertiesExplorerViewPtr view,
                                                                           HierarchicModelAccessPtr modelAccess,
                                                                           SelectionModelPtr selectionModel) {
    return PropertiesExplorerPresenterPtr(new PropertiesExplorerPresenter(view, modelAccess, selectionModel));
}
PropertiesExplorerPresenter::~PropertiesExplorerPresenter() {}
PropertiesExplorerPresenter::PropertiesExplorerPresenter(PropertiesExplorerViewPtr view,
                                                         HierarchicModelAccessPtr modelAccess,
                                                         SelectionModelPtr selectionModel)
        : view(view), modelAccess(modelAccess), selectionModel(selectionModel) {}
void PropertiesExplorerPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void PropertiesExplorerPresenter::update() {
    if(selectionModel->hasSelection())
        view->displayPropertiesFor(modelAccess->retrieve(selectionModel->getSelectedIndex()));
    else
        view->displayEmptyProperties();
}
