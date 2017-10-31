#include "CNDynamicMenuPresenter.h"
#include "CNMenuView.h"
#include "CNVisitableListProvider.h"
#include <Hierarchies/CNComposer/CNComposer.h>

CNDynamicMenuPresenterPtr CNDynamicMenuPresenter::getNewInstance(CNMenuViewPtr view,
                                                                 CNComposerPtr composer,
                                                                 CNVisitableListProviderPtr listProvider) {
    return CNDynamicMenuPresenterPtr(new CNDynamicMenuPresenter(view, composer, listProvider));
}
CNDynamicMenuPresenter::~CNDynamicMenuPresenter() {}
CNDynamicMenuPresenter::CNDynamicMenuPresenter(CNMenuViewPtr view,
                                               CNComposerPtr composer,
                                               CNVisitableListProviderPtr listProvider)
        : view(view), composer(composer), listProvider(listProvider) {}

void CNDynamicMenuPresenter::accept(CNVisitorPtr visitor) {
    view->accept(visitor);
}

void CNDynamicMenuPresenter::update() {
    dismountMenuEntries();
    updateMenuEntries();
    mountMenuEntries();
}

void CNDynamicMenuPresenter::mountMenuEntries() {
    for(int i = 0; i < menuEntries.size(); i++)
        composer->mount(menuEntries[i]);
}

void CNDynamicMenuPresenter::dismountMenuEntries() {
    for(int i = 0; i < menuEntries.size(); i++)
        composer->dismount(menuEntries[i]);
}

void CNDynamicMenuPresenter::updateMenuEntries() {
    menuEntries = listProvider->getVisitables();
}

