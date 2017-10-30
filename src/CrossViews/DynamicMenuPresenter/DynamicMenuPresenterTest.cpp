#include <gmock/gmock.h>
#include "DynamicMenuPresenter.h"
#include "MenuViewTestDoubles.h"
#include "MenuEntryListProviderTestDoubles.h"
#include <CrossHierarchies/CNComposer/CNComposerTestDoubles.h>
#include <CrossHierarchies/CNVisitor/CNVisitorTestDoubles.h>
#include <CrossHierarchies/CNVisitable/CNVisitableTestDoubles.h>

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
    virtual CNComposerPtr makeCNComposerDummy() {
        return CNComposerDummy::getNewInstance();
    }
    virtual MenuEntryListProviderPtr makeMenuEntryListProviderDummy() {
        return MenuEntryListProviderDummy::getNewInstance();
    }
    virtual MenuEntryListProviderStubPtr makeMenuEntryListProviderStub() {
        return MenuEntryListProviderStub::getNewInstance();
    }

    virtual void expectComposerMountedVisitable(CNComposerSpyPtr composer, CNVisitablePtr visitable) {
        CNVisitablePtr expected = visitable;
        CNVisitablePtr actual = composer->getMounted();

        std::string errorMessage = "CNComposer should have mounted the CNVisitable, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectComposerDismountedVisitable(CNComposerSpyPtr composer, CNVisitablePtr visitable) {
        CNVisitablePtr expected = visitable;
        CNVisitablePtr actual = composer->getDismounted();

        std::string errorMessage = "CNComposer should have dismounted the CNVisitable, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectViewAcceptedVisitor(MenuViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The MenuView should have accepted the CNVisitor!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(DynamicMenuPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToTheView) {
    MenuViewSpyPtr view = makeMenuViewSpy();
    CNComposerPtr composer = makeCNComposerDummy();
    MenuEntryListProviderPtr listProvider = makeMenuEntryListProviderDummy();
    DynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectViewAcceptedVisitor(view, visitor);
}

TEST_F(DynamicMenuPresenterTest, FreshInstance__Update__ShouldMountTheProvidedMenuEntry) {
    MenuViewPtr view = makeMenuViewDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    MenuEntryListProviderStubPtr listProvider = makeMenuEntryListProviderStub();
    DynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    listProvider->setMenuEntryList({visitable});

    sut->update();

    expectComposerMountedVisitable(composer, visitable);
}

TEST_F(DynamicMenuPresenterTest, Updated__Update__ShouldDismountThePreviousProvidedMenuEntry) {
    MenuViewPtr view = makeMenuViewDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    MenuEntryListProviderStubPtr listProvider = makeMenuEntryListProviderStub();
    DynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    listProvider->setMenuEntryList({visitable});
    sut->update();

    listProvider->setMenuEntryList({makeCNVisitableDummy()});
    sut->update();

    expectComposerDismountedVisitable(composer, visitable);
}

