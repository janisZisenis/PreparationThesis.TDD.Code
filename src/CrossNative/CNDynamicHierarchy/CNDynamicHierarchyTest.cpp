#include <gmock/gmock.h>

#include "CNDynamicHierarchy.h"

#include "CrossNative/CNComponent/CNComponentTestDoubles.h"
#include "CrossNative/CNComponent/CNFakeComponent.h"

#include "CrossNative/CNMatcher/CNMatcherTestDoubles.h"
#include "CrossNative/CNMatcher/CNFakeMatcher.h"

class CNDynamicHierarchyTest : public testing::Test {
protected:
    virtual CNDynamicHierarchyPtr makeCNDynamicHierarchy() {
        return CNDynamicHierarchy::getNewInstance();
    }
    virtual CNComponentPtr makeCNHierarchyNodeDummy() {
        return CNComponentDummy::getNewInstance();
    }
    virtual CNComponentSpyPtr makeCNHierarchyNodeSpy() {
        return CNComponentSpy::getNewInstance();
    }
    virtual CNComponentPtr makeCNFakeComponent() {
        return CNFakeComponent::getNewInstance();
    }

    virtual CNFakeMatcherPtr makeCNFakeMatcher(CNComponentPtr matching) {
        return CNFakeMatcher::getNewInstance(matching);
    }
    virtual CNMatcherStubPtr makeNotMatchingCNMatcher() {
        CNMatcherStubPtr matcher = makeCNMatcherStub();
        matcher->setIsMatching(false);
        return matcher;
    }
    virtual CNMatcherStubPtr makeCNMatcherStub() {
        return CNMatcherStub::getNewInstance();
    }

    virtual void expectEquals(CNComponentPtr actual, CNComponentPtr expected, std::string errorMessage) {
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectUnequals(CNComponentPtr actual, CNComponentPtr unexpected, std::string errorMessage) {
        EXPECT_THAT(actual, testing::Ne(unexpected)) << errorMessage;
    }

    virtual void expectReceiverAddedComponent(CNComponentSpyPtr receiver, CNComponentPtr component, std::string errorMessage) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = receiver->getAdded();

        expectEquals(actual, expected, errorMessage);
    }
    virtual void expectReceiverDidNotAddComponent(CNComponentSpyPtr receiver, CNComponentPtr component, std::string errorMessage) {
        CNComponentPtr unexpected = component;
        CNComponentPtr actual = receiver->getAdded();

        expectUnequals(actual, unexpected, errorMessage);
    }
    virtual void expectReceiverRemovedComponent(CNComponentSpyPtr receiver, CNComponentPtr component, std::string errorMessage) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = receiver->getRemoved();

        expectEquals(actual, expected, errorMessage);
    }
    virtual void expectReceiverDidNotRemoveComponent(CNComponentSpyPtr receiver, CNComponentPtr component, std::string errorMessage) {
        CNComponentPtr unexpected = component;
        CNComponentPtr actual = receiver->getRemoved();

        expectUnequals(actual, unexpected, errorMessage);
    }

    virtual std::string getReceiverAddedComponentErrorMessage(std::string receiverName, std::string componentName) {
        return componentName + " should be added to " + receiverName + ", but it was not!";
    }
    virtual std::string getReceiverDidNotAddComponentErrorMessage(std::string receiverName, std::string componentName) {
        return componentName + " should not be added to " + receiverName + ", but it was!";
    }
    virtual std::string getReceiverRemovedComponentErrorMessage(std::string receiverName, std::string componentName) {
        return componentName + " should be removed from " + receiverName + ", but it was not!";
    }
    virtual std::string getReceiverDidNotRemoveComponentErrorMessage(std::string receiverName, std::string componentName) {
        return componentName + " should not be removed from " + receiverName + ", but it was!";
    }

    virtual std::string getThrowsCNHierarchyNodeNotLoadedExcpetionErrorMessage() {
        return "CNDynamicComponentHierarchy should throw CNHierarchyNodeNotLoadedException, but it did not!";
    }
};

TEST_F(CNDynamicHierarchyTest, LoadedFirst__LoadSecondMatchingFirst__SecondShouldBeAddedToFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());

    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeCNFakeMatcher(first));

    std::string errorMessage = getReceiverAddedComponentErrorMessage("First", "Second");
    expectReceiverAddedComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst__LoadSecondNotMatching__SecondShouldNotBeAddedToFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());

    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverDidNotAddComponentErrorMessage("First", "Second");
    expectReceiverDidNotAddComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecondMatchingFirst__LoadThirdMatchingSecond__ThirdShouldBeAddedToSecond) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    sut->load(second, makeCNFakeMatcher(first));

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeCNFakeMatcher(second));

    std::string errorMessage = getReceiverAddedComponentErrorMessage("Second", "Third");
    expectReceiverAddedComponent(second, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecondMatchingFirst__LoadThirdNotMatching__ThirdShouldNotBeAddedToSecond) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    sut->load(second, makeCNFakeMatcher(first));

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverDidNotAddComponentErrorMessage("Second", "Third");
    expectReceiverDidNotAddComponent(second, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecondMatchingFirst__LoadThirdMatchingFirst__ThirdShouldBeAddedToFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeCNFakeMatcher(first));

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeCNFakeMatcher(first));

    std::string errorMessage = getReceiverAddedComponentErrorMessage("First", "Third");
    expectReceiverAddedComponent(first, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecondMatchingFirst__LoadThirdNotMatching__ThirdShouldNotBeAddedToFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeCNFakeMatcher(first));

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverDidNotAddComponentErrorMessage("First", "Third");
    expectReceiverDidNotAddComponent(first, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecondMatchingFirst__LoadThirdMatchingFirst__ThirdShouldNotBeAddedToSecond) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent()  ;
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    sut->load(second, makeCNFakeMatcher(first));

    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeCNFakeMatcher(first));

    std::string errorMessage = getReceiverDidNotAddComponentErrorMessage("Second", "Third");
    expectReceiverDidNotAddComponent(second, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst__LoadFirst__ShouldThrowCNAlreadyLoadedException) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNHierarchyNodeDummy();
    sut->load(first, makeNotMatchingCNMatcher());

    std::string errorMessage = "CNDynamicHierarchy should throw CNHierarchyNodeAlreadyLoadedException, but it did not!";
    EXPECT_THROW(sut->load(first, makeNotMatchingCNMatcher()), CNHierarchyNodeAlreadyLoadedException) << errorMessage;
}


TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_FirstIsParent__UnloadSecond__SecondShouldBeRemovedFromFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    first->setIsParentOf(true);
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeCNFakeMatcher(first));

    sut->unload(second);

    std::string errorMessage = getReceiverRemovedComponentErrorMessage("Second", "First");
    expectReceiverRemovedComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_FirstIsNotParent__UnloadSecond__SecondShouldNotBeRemovedFromFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    first->setIsParentOf(false);
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeNotMatchingCNMatcher());

    sut->unload(second);

    std::string errorMessage = getReceiverDidNotRemoveComponentErrorMessage("Second", "First");
    expectReceiverDidNotRemoveComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_LoadedThird_SecondIsParent__UnloadThird__ThirdShouldBeRemovedFromSecond) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    second->setIsParentOf(true);
    sut->load(second, makeCNFakeMatcher(first));
    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeCNFakeMatcher(second));

    sut->unload(third);

    std::string errorMessage = getReceiverRemovedComponentErrorMessage("Second", "Third");
    expectReceiverRemovedComponent(second, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_LoadedThird_SecondIsNotParent__UnloadThird__ThirdShouldNotBeRemovedFromSecond) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentSpyPtr second = makeCNHierarchyNodeSpy();
    second->setIsParentOf(false);
    sut->load(second, makeCNFakeMatcher(first));
    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeNotMatchingCNMatcher());

    sut->unload(third);

    std::string errorMessage = getReceiverDidNotRemoveComponentErrorMessage("Second", "Third");
    expectReceiverDidNotRemoveComponent(second, third, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, FreshInstance__UnloadFirst__ShouldThrowCNHierarchyNodeNotLoadedException) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();

    CNComponentPtr first = makeCNHierarchyNodeDummy();

    std::string errorMessage = getThrowsCNHierarchyNodeNotLoadedExcpetionErrorMessage();
    EXPECT_THROW(sut->unload(first), CNHierarchyNodeNotLoadedException) << errorMessage;
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst__UnloadSecond__ShouldThrowCNHierarchyNodeNotLoadedException) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent();
    sut->load(first, makeNotMatchingCNMatcher());

    CNComponentPtr second = makeCNHierarchyNodeDummy();

    std::string errorMessage = getThrowsCNHierarchyNodeNotLoadedExcpetionErrorMessage();
    EXPECT_THROW(sut->unload(second), CNHierarchyNodeNotLoadedException) << errorMessage;
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond__UnloadThird__ShouldThrowCNHierarchyNodeNotLoadedException) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentPtr first = makeCNFakeComponent();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeNotMatchingCNMatcher());

    CNComponentPtr third = makeCNHierarchyNodeDummy();

    std::string errorMessage = getThrowsCNHierarchyNodeNotLoadedExcpetionErrorMessage();
    EXPECT_THROW(sut->unload(third), CNHierarchyNodeNotLoadedException) << errorMessage;
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_LoadedThird_FirstIsParent__UnloadSecond__SecondShouldBeRemovedFromFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    first->setIsParentOf(true);
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeCNFakeMatcher(first));
    CNComponentPtr third = makeCNHierarchyNodeDummy();
    sut->load(third, makeNotMatchingCNMatcher());

    sut->unload(second);

    std::string errorMessage = getReceiverRemovedComponentErrorMessage("First", "Second");
    expectReceiverRemovedComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_UnloadedSecond__LoadSecondMatchingFirst_SecondShouldBeAddedToFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeNotMatchingCNMatcher());
    sut->unload(second);

    sut->load(second, makeCNFakeMatcher(first));

    std::string errorMessage = getReceiverAddedComponentErrorMessage("First", "Second");
    expectReceiverAddedComponent(first, second, errorMessage);
}


TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecond_FirstIsParent__MoveSecondNotMatching__SecondShouldBeRemovedFromFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    first->setIsParentOf(true);
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeCNFakeMatcher(first));

    sut->move(second, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverRemovedComponentErrorMessage("First", "Second");
    expectReceiverRemovedComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst_LoadedSecondNotMatching__MoveSecondMatchingFirst__SecondShouldBeAddedToFirst) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());
    CNComponentPtr second = makeCNHierarchyNodeDummy();
    sut->load(second, makeNotMatchingCNMatcher());

    sut->move(second, makeCNFakeMatcher(first));

    std::string errorMessage = getReceiverAddedComponentErrorMessage("First", "Second");
    expectReceiverAddedComponent(first, second, errorMessage);
}

TEST_F(CNDynamicHierarchyTest, LoadedFirst__MoveSecond__ShouldThrowCNHierarchyNodeNotLoadedException) {
    CNDynamicHierarchyPtr sut = makeCNDynamicHierarchy();
    CNComponentSpyPtr first = makeCNHierarchyNodeSpy();
    sut->load(first, makeNotMatchingCNMatcher());

    CNComponentPtr second = makeCNHierarchyNodeDummy();

    std::string errorMessage = getThrowsCNHierarchyNodeNotLoadedExcpetionErrorMessage();
    EXPECT_THROW(sut->move(second, makeNotMatchingCNMatcher()), CNHierarchyNodeNotLoadedException) << errorMessage;
}