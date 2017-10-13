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

    virtual CNComposerSpyPtr makeCNComposerSpy() {
        return CNComposerSpy::getNewInstance();
    }

    virtual void expectComposerMountedComponent(CNComposerSpyPtr composer, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = composer->getMounted();

        std::string errorMessage = "Composer should have mounted component, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNComposableTest, FreshIntance__Add__ComposerShouldHaveMountedTheAddedComponent) {
    CNComposerSpyPtr composer = makeCNComposerSpy();
    CNComposablePtr sut = makeCNComposable(composer);

    CNComponentPtr component = makeCNComponentDummy();
    sut->add(component);

    expectComposerMountedComponent(composer, component);
}
