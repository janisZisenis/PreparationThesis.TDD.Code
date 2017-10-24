#include <gmock/gmock.h>
#include "DynamicMenuPresenter.h"
#include "MenuViewTestDoubles.h"
#include "MenuEntryListProviderTestDoubles.h"
#include <CrossNative/CNComposer/CNComposerTestDoubles.h>
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>

class DynamicMenuPresenterTest : public testing::Test {
protected:
    virtual DynamicMenuPresenterPtr makeDynamicMenuPresenter(MenuViewPtr view,
                                                             CNComposerPtr composer,
                                                             MenuEntryListProviderPtr listProvider) {
        return DynamicMenuPresenter::getNewInstance(view, composer, listProvider);
    }
    virtual MenuViewPtr makeMenuViewDummy() {
        return MenuViewDummy::getNewInstance();
    }
    virtual MenuViewSpyPtr makeMenuViewSpy() {
        return MenuViewSpy::getNewInstance();
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }
    virtual CNComposerSpyPtr makeCNComposerSpy() {
        return CNComposerSpy::getNewInstance();
    }
    virtual MenuEntryListProviderPtr makeMenuEntryListProviderDummy() {
        return MenuEntryListProviderDummy::getNewInstance();
    }
    virtual MenuEntryListProviderStubPtr makeMenuEntryListProviderStub() {
        return MenuEntryListProviderStub::getNewInstance();
    }

    virtual void expectMenuViewWasCleared(MenuViewSpyPtr view) {
        bool actual = view->wasCleared();

        std::string errorMessage = "DynamicMenuPresenter should have cleared the MenuView, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }

    virtual void expectComposerMountedVisitable(CNComposerSpyPtr composer, CNVisitablePtr visitable) {
        CNVisitablePtr expected = visitable;
        CNVisitablePtr actual = composer->getMounted();

        std::string errorMessage = "CNComposer should have mounted the CNVisitable, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(DynamicMenuPresenterTest, FreshInstance__Update__ShouldClearTheMenuView) {
    MenuViewSpyPtr view = makeMenuViewSpy();
    CNComposerPtr composer = makeCNComposerSpy();
    MenuEntryListProviderPtr listProvider = makeMenuEntryListProviderDummy();
    DynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);

    sut->update();

    expectMenuViewWasCleared(view);
}

TEST_F(DynamicMenuPresenterTest, FreshInstance__Update__ShouldMountTheProvidedMenuEntry) {
    MenuViewPtr view = makeMenuViewDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    MenuEntryListProviderStubPtr listProvider = MenuEntryListProviderStub::getNewInstance();
    DynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    listProvider->addMenuEntryList(visitable);

    sut->update();

    expectComposerMountedVisitable(composer, visitable);
}

