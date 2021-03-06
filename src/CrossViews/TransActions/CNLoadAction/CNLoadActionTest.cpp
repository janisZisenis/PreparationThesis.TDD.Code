#include <gmock/gmock.h>
#include "CNLoadAction.h"
#include <Hierarchies/CNComponent/CNComponentTestDoubles.h>
#include "CNComponentLoaderTestDoubles.h"
#include "CNCreateComponentStrategyTestDoubles.h"
#include <Hierarchies/CNMatcher/CNMatcherTestDoubles.h>

class CNLoadActionTest : public testing::Test {
protected:
    virtual CNLoadActionPtr makeCNLoadAction(CNComponentLoaderPtr loader,
                                             CNCreateComponentStrategyPtr componentStrategy,
                                             CNMatcherPtr matcher) {
        return CNLoadAction::getNewInstance(loader, componentStrategy, matcher);
    }
    virtual CNMatcherPtr makeCNMatcherDummy() {
        return CNMatcherDummy::getNewInstance();
    }
    virtual CNCreateComponentStrategyStubPtr makeCNCreateComponentStrategyStub() {
        return CNCreateComponentStrategyStub::getNewInstance();
    }
    virtual CNCreateComponentStrategyPtr makeCNCreateComponentStrategySaboteur() {
        return CNCreateComponentStrategySaboteur::getNewInstance();
    }
    virtual CNComponentLoaderPtr makeCNComponentLoaderDummy() {
        return CNComponentLoaderDummy::getNewInstance();
    }
    virtual CNComponentLoaderSpyPtr makeCNComponentLoaderSpy() {
        return CNComponentLoaderSpy::getNewInstance();
    }
    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual void expectCNComponentWasLoadedWithMatcher(CNComponentPtr component, CNMatcherPtr matcher, CNComponentLoaderSpyPtr loader) {
        expectCNComponentLoaderLoadedComponent(loader, component);
        expectCNComponentLoadedMatcher(loader, matcher);
    }
    virtual void expectCNComponentLoaderLoadedComponent(CNComponentLoaderSpyPtr loader, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = loader->getLoadedComponent();

        std::string errorMessage = "CNComponentLoader should have loaded the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectCNComponentLoadedMatcher(CNComponentLoaderSpyPtr loader, CNMatcherPtr matcher) {
        CNMatcherPtr expected = matcher;
        CNMatcherPtr actual = loader->getLoadedMatcher();

        std::string errorMessage = "CNComponentLoader should have loaded the CNMatcher, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectCNComponentWasNotLoaded(CNComponentLoaderSpyPtr loader) {
        bool actual = loader->loadedWasCalled();

        std::string errorMessage = "CNComponentLoader should not have loaded a component, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(CNLoadActionTest, FreshInstance__Execute__ShouldLoadCNComponentToCNComponenLoaderWithCNMatcher) {
    CNCreateComponentStrategyStubPtr componentStrategy = makeCNCreateComponentStrategyStub();
    CNComponentPtr component = makeCNComponentDummy();
    componentStrategy->setCNComponent(component);
    CNMatcherPtr matcher = makeCNMatcherDummy();
    CNComponentLoaderSpyPtr componentLoader = makeCNComponentLoaderSpy();
    CNLoadActionPtr sut = makeCNLoadAction(componentLoader, componentStrategy, matcher);

    sut->execute();

    expectCNComponentWasLoadedWithMatcher(component, matcher, componentLoader);
}

TEST_F(CNLoadActionTest, ComponentStrategyThrowsCreationCanceledException__Execute__ShouldNotLoadCNComponentToCNComponenLoader) {
    CNCreateComponentStrategyPtr componentStrategy = makeCNCreateComponentStrategySaboteur();
    CNComponentPtr component = makeCNComponentDummy();
    CNMatcherPtr matcher = makeCNMatcherDummy();
    CNComponentLoaderSpyPtr componentLoader = makeCNComponentLoaderSpy();
    CNLoadActionPtr sut = makeCNLoadAction(componentLoader, componentStrategy, matcher);

    sut->execute();

    expectCNComponentWasNotLoaded(componentLoader);
}