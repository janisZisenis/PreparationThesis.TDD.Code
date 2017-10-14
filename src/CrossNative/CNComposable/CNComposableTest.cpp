#include <gmock/gmock.h>
#include "CNComposable.h"

#include "CrossNative/CNComponent/CNComponentTestDoubles.h"
#include "CrossNative/CNComposer/CNComposerTestDoubles.h"
#include "CrossNative/CNVisitable/CNVisitableTestDoubles.h"
#include "CrossNative/CNVisitor/CNVisitorTestDoubles.h"

class CNComposableTest : public testing::Test {
protected:
    virtual CNComposablePtr makeCNComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
        return CNComposable::getNewInstance(visitable, composer);
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual CNComposerPtr makeCNComposerDummy() {
        return CNComposerDummy::getNewInstance();
    }
    virtual CNComposerSpyPtr makeCNComposerSpy() {
        return CNComposerSpy::getNewInstance();
    }

    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }
    virtual CNVisitableSpyPtr makeCNVisitableSpy() {
        return CNVisitableSpy::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }

    virtual void expectIsParentOfComponent(CNComposablePtr sut, CNComponentPtr component) {
        bool expected = sut->isParentOf(component);

        std::string errorMessage = "CNComposable should be parent of component, but it is not!";
        EXPECT_TRUE(expected) << errorMessage;
    }
    virtual void expectIsNotParentOfComponent(CNComposablePtr sut, CNComponentPtr component) {
        bool expected = sut->isParentOf(component);

        std::string errorMessage = "CNComposable should not be parent of component, but it is!";
        EXPECT_FALSE(expected) << errorMessage;
    }

    virtual void expectComposerMountedChild(CNComposerSpyPtr composer, CNComponentPtr child) {
        CNComponentPtr expected = child;
        CNComponentPtr actual = composer->getMounted();

        std::string errorMessage = "Composer should have mounted child, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectComposerDismountedChild(CNComposerSpyPtr composer, CNComponentPtr child) {
        CNComponentPtr expected = child;
        CNComponentPtr actual = composer->getDismounted();

        std::string errorMessage = "Composer should have dismounted child, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectVisitableHasAcceptedVisitor(CNVisitableSpyPtr visitable, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitable->getAccepted();
        CNVisitorPtr actual = visitor;

        std::string errorMessage = "The visitable should have accepted the visitor, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNComposableTest, FreshIntance__AddChild__ComposerShouldMountedTheAddedChild) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);

    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectComposerMountedChild(composer, child);
}

TEST_F(CNComposableTest, FreshInstance__AddChild__SUTShouldBeParentOfChild) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerPtr composer = makeCNComposerDummy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);

    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectIsParentOfComponent(sut, child);
}

TEST_F(CNComposableTest, ChildAdded__RemoveChild__ComposerShouldDismountTheRemovedChild) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(child);

    expectComposerDismountedChild(composer, child);
}

TEST_F(CNComposableTest, ChildAdded__RemoveChild__SUTShouldNotBeParentOfChild) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(child);

    expectIsNotParentOfComponent(sut, child);
}

TEST_F(CNComposableTest, FreshInstance__RemoveChild__ShouldThrowCNChildNotFoundException) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerPtr composer = makeCNComposerDummy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);

    CNComponentPtr child = makeCNComponentDummy();

    std::string errorMessage = "CNComposable should throw CNChildNotFoundException, but it did not";
    EXPECT_THROW(sut->remove(child), CNChildNotFoundException) << errorMessage;
}

TEST_F(CNComposableTest, TwoChildrenAdded__RemoveSecond__SUTShouldNotBeParentOfSecond) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);
    CNComponentPtr first = makeCNComponentDummy();
    sut->add(first);
    CNComponentPtr second= makeCNComponentDummy();
    sut->add(second);

    sut->remove(second);

    expectIsNotParentOfComponent(sut, second);
}

TEST_F(CNComposableTest, ChildrenAdded__Destruction__ComposerShouldDismountTheChild) {
    CNVisitablePtr visitable = makeCNVisitableDummy();
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut.reset();

    expectComposerDismountedChild(composer, child);
}


TEST_F(CNComposableTest, FreshInstance__Accept__VisitableShouldHaveAcceptedVisitor) {
    CNVisitableSpyPtr visitable = makeCNVisitableSpy();
    CNComposerPtr composer = makeCNComposerDummy();
    CNComposablePtr sut = makeCNComposable(visitable, composer);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectVisitableHasAcceptedVisitor(visitable, visitor);
}