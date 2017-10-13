#include <gmock/gmock.h>
#include "CNComposable.h"

#include "CrossNative/CNComponent/CNComponentTestDoubles.h"
#include "CrossNative/CNComposer/CNComposerTestDoubles.h"

class CNComposableTest : public testing::Test {
protected:
    virtual CNComposablePtr makeCNComposable(CNComposerPtr composer) {
        return CNComposable::getNewInstance(composer);
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

    virtual void expectIsParentOfComponent(CNComposablePtr sut, CNComponentPtr component) {
        bool expected = sut->isParentOf(component);

        std::string errorMessage = "CNComposable should be parent of component, but it is not!";
        EXPECT_TRUE(expected) << errorMessage;
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
};

TEST_F(CNComposableTest, FreshIntance__AddChild__ComposerShouldHaveMountedTheAddedChild) {
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(composer);

    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectComposerMountedChild(composer, child);
}

TEST_F(CNComposableTest, ChildAdded__RemoveChild__ComposerShouldHaveDismountedTheRemovedChild) {
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(composer);
    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    sut->remove(child);

    expectComposerDismountedChild(composer, child);
}

TEST_F(CNComposableTest, FreshInstance__AddChild__SUTShouldBeNotParentOfChild) {
    CNComposerPtr composer = makeCNComposerDummy();
    CNComposablePtr sut = makeCNComposable(composer);

    CNComponentPtr child = makeCNComponentDummy();
    sut->add(child);

    expectIsParentOfComponent(sut, child);
}