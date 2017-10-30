#include <gmock/gmock.h>
#include "LoadAction.h"
#include "CrossHierarchies/CNComponent/CNComponentTestDoubles.h"
#include "ComponentLoaderTestDoubles.h"
#include "CreateComponentStrategyTestDoubles.h"
#include "CrossHierarchies/CNMatcher/CNMatcherTestDoubles.h"

class LoadActionTest : public testing::Test {
protected:
    virtual LoadActionPtr makeCNLoadAction(ComponentLoaderPtr loader,
                                             CreateComponentStrategyPtr componentStrategy,
                                             CNMatcherPtr matcher) {
        return LoadAction::getNewInstance(loader, componentStrategy, matcher);
    }
    virtual CNMatcherPtr makeCNMatcherDummy() {
        return CNMatcherDummy::getNewInstance();
    }
    virtual CreateComponentStrategyStubPtr makeCNCreateComponentStrategyStub() {
        return CreateComponentStrategyStub::getNewInstance();
    }
    virtual CreateComponentStrategyPtr makeCNCreateComponentStrategySaboteur() {
        return CreateComponentStrategySaboteur::getNewInstance();
    }
    virtual ComponentLoaderPtr makeCNComponentLoaderDummy() {
        return ComponentLoaderDummy::getNewInstance();
    }
    virtual ComponentLoaderSpyPtr makeCNComponentLoaderSpy() {
        return ComponentLoaderSpy::getNewInstance();
    }
    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual void expectCNComponentWasLoadedWithMatcher(CNComponentPtr component, CNMatcherPtr matcher, ComponentLoaderSpyPtr loader) {
        expectCNComponentLoaderLoadedComponent(loader, component);
        expectCNComponentLoadedMatcher(loader, matcher);
    }
    virtual void expectCNComponentLoaderLoadedComponent(ComponentLoaderSpyPtr loader, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = loader->getLoadedComponent();

        std::string errorMessage = "ComponentLoader should have loaded the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectCNComponentLoadedMatcher(ComponentLoaderSpyPtr loader, CNMatcherPtr matcher) {
        CNMatcherPtr expected = matcher;
        CNMatcherPtr actual = loader->getLoadedMatcher();

        std::string errorMessage = "ComponentLoader should have loaded the CNMatcher, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectCNComponentWasNotLoaded(ComponentLoaderSpyPtr loader) {
        bool actual = loader->loadedWasCalled();

        std::string errorMessage = "ComponentLoader should not have loaded a component, but it has!";
        EXPECT_FALSE(actual) << errorMessage;
    }
};

TEST_F(LoadActionTest, FreshInstance__Execute__ShouldLoadCNComponentToCNComponenLoaderWithCNMatcher) {
    CreateComponentStrategyStubPtr componentStrategy = makeCNCreateComponentStrategyStub();
    CNComponentPtr component = makeCNComponentDummy();
    componentStrategy->setCNComponent(component);
    CNMatcherPtr matcher = makeCNMatcherDummy();
    ComponentLoaderSpyPtr componentLoader = makeCNComponentLoaderSpy();
    LoadActionPtr sut = makeCNLoadAction(componentLoader, componentStrategy, matcher);

    sut->execute();

    expectCNComponentWasLoadedWithMatcher(component, matcher, componentLoader);
}

TEST_F(LoadActionTest, ComponentStrategyThrowsCreationCanceledException__Execute__ShouldNotLoadCNComponentToCNComponenLoader) {
    CreateComponentStrategyPtr componentStrategy = makeCNCreateComponentStrategySaboteur();
    CNComponentPtr component = makeCNComponentDummy();
    CNMatcherPtr matcher = makeCNMatcherDummy();
    ComponentLoaderSpyPtr componentLoader = makeCNComponentLoaderSpy();
    LoadActionPtr sut = makeCNLoadAction(componentLoader, componentStrategy, matcher);

    sut->execute();

    expectCNComponentWasNotLoaded(componentLoader);
}