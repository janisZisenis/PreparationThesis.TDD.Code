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

void DynamicMenuPresenter::accept(CNVisitorPtr visitor) {}

void DynamicMenuPresenter::update() {
    view->clear();

    std::vector<CNVisitablePtr> menuEntryList = listProvider->getMenuEntryList();
    for(int i = 0; i < menuEntryList.size(); i++)
        composer->mount(menuEntryList[i]);
}
