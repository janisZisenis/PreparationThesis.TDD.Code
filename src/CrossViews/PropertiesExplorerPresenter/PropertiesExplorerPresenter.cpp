#include "PropertiesExplorerPresenter.h"
#include "PropertiesExplorerView.h"

PropertiesExplorerPresenterPtr PropertiesExplorerPresenter::getNewInstance(PropertiesExplorerViewPtr view) {
    return PropertiesExplorerPresenterPtr(new PropertiesExplorerPresenter(view));
}
PropertiesExplorerPresenter::~PropertiesExplorerPresenter() {}
PropertiesExplorerPresenter::PropertiesExplorerPresenter(PropertiesExplorerViewPtr view) : view(view) {}
void PropertiesExplorerPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}