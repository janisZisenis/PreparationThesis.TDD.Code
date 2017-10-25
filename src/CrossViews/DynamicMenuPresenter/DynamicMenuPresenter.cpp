#include "DynamicMenuPresenter.h"
#include "MenuView.h"
#include "MenuEntryListProvider.h"
#include <CrossNative/CNComposer/CNComposer.h>

DynamicMenuPresenterPtr DynamicMenuPresenter::getNewInstance(MenuViewPtr view,
                                                             CNComposerPtr composer,
                                                             MenuEntryListProviderPtr listProvider) {
    return DynamicMenuPresenterPtr(new DynamicMenuPresenter(view, composer, listProvider));
}
DynamicMenuPresenter::~DynamicMenuPresenter() {}
DynamicMenuPresenter::DynamicMenuPresenter(MenuViewPtr view,
                                           CNComposerPtr composer,
                                           MenuEntryListProviderPtr listProvider)
        : view(view), composer(composer), listProvider(listProvider) {}

void DynamicMenuPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void DynamicMenuPresenter::update() {
    dismountMenuEntries();
    updateMenuEntries();
    mountMenuEntries();
}

void DynamicMenuPresenter::mountMenuEntries() {
    for(int i = 0; i < menuEntries.size(); i++)
        composer->mount(menuEntries[i]);
}

void DynamicMenuPresenter::dismountMenuEntries() {
    for(int i = 0; i < menuEntries.size(); i++)
        composer->dismount(menuEntries[i]);
}

void DynamicMenuPresenter::updateMenuEntries() {
    menuEntries = listProvider->getMenuEntryList();
}

