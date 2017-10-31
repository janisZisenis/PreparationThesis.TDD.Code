#include <gmock/gmock.h>
#include "CNDynamicMenuPresenter.h"
#include "CNMenuViewTestDoubles.h"
#include "CNVisitableListProviderTestDoubles.h"
#include <Hierarchies/CNComposer/CNComposerTestDoubles.h>
#include <Hierarchies/CNVisitor/CNVisitorTestDoubles.h>
#include <Hierarchies/CNVisitable/CNVisitableTestDoubles.h>

class CNDynamicMenuPresenterTest : public testing::Test {
protected:
    virtual CNDynamicMenuPresenterPtr makeDynamicMenuPresenter(CNMenuViewPtr view,
                                                             CNComposerPtr composer,
                                                             CNVisitableListProviderPtr listProvider) {
        return CNDynamicMenuPresenter::getNewInstance(view, composer, listProvider);
    }
    virtual CNMenuViewPtr makeMenuViewDummy() {
        return CNMenuViewDummy::getNewInstance();
    }
    virtual CNMenuViewSpyPtr makeMenuViewSpy() {
        return CNMenuViewSpy::getNewInstance();
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
    virtual CNVisitableListProviderPtr makeVisitableListProviderDummy() {
        return CNVisitableListProviderDummy::getNewInstance();
    }
    virtual CNVisitableListProviderStubPtr makeVisitableListProviderStub() {
        return CNVisitableListProviderStub::getNewInstance();
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
    virtual void expectViewAcceptedVisitor(CNMenuViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The CNMenuView should have accepted the CNVisitor!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNDynamicMenuPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToTheView) {
    CNMenuViewSpyPtr view = makeMenuViewSpy();
    CNComposerPtr composer = makeCNComposerDummy();
    CNVisitableListProviderPtr listProvider = makeVisitableListProviderDummy();
    CNDynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectViewAcceptedVisitor(view, visitor);
}

TEST_F(CNDynamicMenuPresenterTest, FreshInstance__Update__ShouldMountTheProvidedMenuEntry) {
    CNMenuViewPtr view = makeMenuViewDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNVisitableListProviderStubPtr listProvider = makeVisitableListProviderStub();
    CNDynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    listProvider->setMenuEntryList({visitable});

    sut->update();

    expectComposerMountedVisitable(composer, visitable);
}

TEST_F(CNDynamicMenuPresenterTest, Updated__Update__ShouldDismountThePreviousProvidedMenuEntry) {
    CNMenuViewPtr view = makeMenuViewDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNVisitableListProviderStubPtr listProvider = makeVisitableListProviderStub();
    CNDynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer, listProvider);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    listProvider->setMenuEntryList({visitable});
    sut->update();

    listProvider->setMenuEntryList({makeCNVisitableDummy()});
    sut->update();

    expectComposerDismountedVisitable(composer, visitable);
}

