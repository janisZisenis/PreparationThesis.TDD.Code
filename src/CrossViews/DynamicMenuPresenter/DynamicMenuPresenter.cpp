#include "DynamicMenuPresenter.h"
#include "MenuView.h"
#include <CrossNative/CNComposer/CNComposer.h>

DynamicMenuPresenterPtr DynamicMenuPresenter::getNewInstance(MenuViewPtr view, CNComposerPtr composer) {
    return DynamicMenuPresenterPtr(new DynamicMenuPresenter(view, composer));
}
DynamicMenuPresenter::~DynamicMenuPresenter() {}
DynamicMenuPresenter::DynamicMenuPresenter(MenuViewPtr view, CNComposerPtr composer)
        : view(view), composer(composer) {}

void DynamicMenuPresenter::accept(CNVisitorPtr visitor) {}

void DynamicMenuPresenter::update() {

}
